/*
 * MIT License
 *
 * Copyright (c) 2020-2023 EntySec
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>

#include <log.h>
#include <tlv.h>
#include <api.h>
#include <tab.h>
#include <node.h>
#include <console.h>
#include <c2.h>
#include <tlv_types.h>

#include <uthash/uthash.h>

c2_t *c2_create(int id, int fd, char *name)
{
    c2_t *c2 = calloc(1, sizeof(*c2));

    if (c2 != NULL)
    {
        c2->id = id;
        c2->fd = fd;
        c2->name = strdup(name);
        c2->tlv_pkt = NULL;

        c2->dynamic.t_count = 0;
        c2->dynamic.n_count = 0;
        c2->dynamic.tabs = NULL;
        c2->dynamic.nodes = NULL;
        c2->dynamic.api_calls = NULL;

        return c2;
    }

    return NULL;
}

int c2_write(c2_t *c2, tlv_pkt_t *tlv_pkt)
{
    return tlv_pkt_write(c2->fd, tlv_pkt);
}

int c2_read(c2_t *c2)
{
    c2->tlv_pkt = tlv_pkt_create();

    if (c2->tlv_pkt != NULL)
        return tlv_pkt_read(c2->fd, c2->tlv_pkt);

    return -1;
}

void c2_add(c2_t **c2_table, int id, int fd, char *name)
{
    c2_t *c2;
    HASH_FIND_INT(*c2_table, &id, c2);

    if (c2 == NULL)
    {
        c2_t *c2_new = c2_create(id, fd, name);

        if (c2_new != NULL)
        {
            HASH_ADD_INT(*c2_table, id, c2_new);
            log_debug("* Added net C2 entry (%d) - (%s)\n", id, name);
        }
    }
}

void c2_init(c2_t *c2_table)
{
    c2_t *c2;

    for (c2 = c2_table; c2 != NULL; c2 = c2->hh.next)
    {
        log_debug("* Initializing net C2 server (%d) - (%s)\n",
                  c2->id, c2->name);
        tlv_pkt_t *tlv_pkt = tlv_pkt_create();

        if (tlv_pkt != NULL)
        {
            if (tlv_pkt_add_string(tlv_pkt, TLV_TYPE_UUID, c2->name) == 0)
            {
                log_debug("* Writing net C2 server name (%s)\n", c2->name);

                if (c2_write(c2, tlv_pkt) != 0)
                    tlv_pkt_destroy(tlv_pkt);
                else
                    tlv_console_loop(c2);

            } else
                tlv_pkt_destroy(tlv_pkt);
        }

        HASH_DEL(c2_table, c2);

        tabs_free(c2->dynamic.tabs);
        nodes_free(c2->dynamic.nodes);
        api_calls_free(c2->dynamic.api_calls);

        free(c2->name);
        free(c2);
    }

    free(c2_table);
}
