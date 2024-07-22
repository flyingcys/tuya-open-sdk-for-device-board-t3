/*
 * Diffie-Hellman group 5 operations
 * Copyright (c) 2009, 2012, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#include "includes.h"

#include "common.h"
#include "dh_groups.h"
#include "dh_group5.h"


#ifdef CONFIG_BK_WPS_WORKAROUND
/*
 * dh key pairs are generated in advance.
 * FIXME: P2P don't hardcode key pairs.
 */
/* DH Private Key, 1536 bits */
static unsigned char g_dh_private_key[192] = {
    0x5F, 0x4B, 0xCA, 0x16, 0xA6, 0x2D, 0xF5, 0xED, 0x33, 0x8D, 0xF0, 0x1F, 0x1D, 0xEC, 0xE6, 0xDE,
    0x61, 0x2E, 0x36, 0x18, 0xB0, 0xCB, 0x15, 0x5D, 0x81, 0x36, 0x98, 0x87, 0x13, 0x4B, 0xFB, 0x52,
    0x37, 0x8B, 0x3F, 0x3D, 0x1F, 0xDF, 0xD6, 0x05, 0xCF, 0x01, 0xA0, 0x96, 0xFD, 0x16, 0xF2, 0x94,
    0x82, 0xE8, 0x0D, 0x5A, 0xA4, 0x34, 0xFD, 0x98, 0xED, 0x14, 0xF3, 0x2C, 0x26, 0x3F, 0x04, 0xC4,
    0x28, 0x91, 0x81, 0x99, 0x70, 0x85, 0x4C, 0x52, 0x20, 0xCD, 0x2B, 0xB0, 0xC2, 0x9B, 0xBB, 0x3A,
    0x69, 0xB8, 0x1E, 0x97, 0xB5, 0x18, 0xBF, 0x84, 0x02, 0x87, 0x56, 0x73, 0xDA, 0xEA, 0x3E, 0xEB,
    0x03, 0x53, 0x1D, 0xB2, 0xBD, 0xB1, 0xC0, 0x85, 0x16, 0x3C, 0x22, 0x58, 0xDD, 0x2B, 0xF9, 0x18,
    0xC9, 0x54, 0xD7, 0x4E, 0xE6, 0xC3, 0xBB, 0x61, 0xC5, 0x20, 0xB1, 0x28, 0x21, 0x8F, 0xF0, 0xAD,
    0x7B, 0x99, 0x1A, 0x52, 0x42, 0xEF, 0x8C, 0x32, 0xC8, 0xBE, 0xDF, 0x31, 0xA2, 0x35, 0x86, 0x28,
    0x86, 0x7E, 0x73, 0xF4, 0x9D, 0xBF, 0x6C, 0x74, 0x4C, 0x0A, 0x00, 0x75, 0xF1, 0xF5, 0x72, 0x4A,
    0x5E, 0x8E, 0x22, 0x00, 0x95, 0x50, 0xA3, 0xCF, 0x4A, 0xD5, 0xFA, 0x72, 0xD3, 0x6B, 0x77, 0x33,
    0xF2, 0x00, 0x21, 0x97, 0x70, 0x3C, 0x15, 0xDE, 0x6E, 0xF7, 0x53, 0x10, 0xE8, 0x23, 0xF9, 0x4E
};

/* DH Public key, 1536 bits */
static unsigned char g_dh_public_key[192] = {
    0x20, 0xB0, 0x05, 0x0D, 0xF2, 0x14, 0x04, 0x60, 0xE1, 0x39, 0x9E, 0xC7, 0xD4, 0x24, 0xD9, 0x23,
    0x61, 0xF7, 0x72, 0xAB, 0xEB, 0x9F, 0x08, 0x9B, 0xAF, 0xAC, 0x98, 0x03, 0x07, 0xCC, 0xDA, 0x7E,
    0xE8, 0xE9, 0x6E, 0x17, 0xF0, 0xBE, 0x1A, 0xB6, 0xAA, 0x15, 0xF6, 0x98, 0x06, 0xC7, 0x52, 0x4F,
    0xBD, 0xC0, 0x94, 0xEB, 0x24, 0x87, 0x1B, 0x79, 0xA9, 0xF6, 0xC9, 0x40, 0x9A, 0xC5, 0xFB, 0x53,
    0x8D, 0x6F, 0xB1, 0xF9, 0xE4, 0xCF, 0xB0, 0x38, 0xDD, 0x1B, 0x86, 0x99, 0x8D, 0x12, 0x8F, 0x0A,
    0xC2, 0x6D, 0x0B, 0x5C, 0x36, 0x27, 0xDB, 0xBE, 0x66, 0x0D, 0x96, 0x94, 0xFD, 0xD8, 0x6A, 0x8E,
    0x01, 0x2C, 0xDF, 0xFE, 0xF9, 0xC5, 0xD8, 0xD9, 0x53, 0x60, 0xE8, 0x78, 0x29, 0xFB, 0x36, 0x4B,
    0x36, 0xB9, 0x69, 0xA9, 0x1B, 0x8E, 0x78, 0x0E, 0x3A, 0x55, 0x21, 0x90, 0x13, 0x32, 0x56, 0xAE,
    0xB6, 0xB3, 0x8A, 0xAE, 0x8D, 0x1C, 0xB4, 0xB0, 0xC3, 0xC0, 0xE3, 0x8B, 0xFA, 0xA3, 0xC7, 0x75,
    0xCC, 0xBE, 0xA9, 0xC5, 0xCC, 0x6B, 0x8E, 0x9E, 0x88, 0x13, 0xC2, 0xB0, 0xA8, 0xB4, 0x73, 0xC8,
    0x0B, 0x18, 0xD9, 0xE1, 0xA8, 0x90, 0x3D, 0x4A, 0xE5, 0x55, 0xC6, 0x05, 0x65, 0x7A, 0x14, 0x58,
    0xE8, 0x66, 0xBE, 0x0F, 0x28, 0x6C, 0x1D, 0xDD, 0xEC, 0x4A, 0xAD, 0x11, 0xD0, 0x5A, 0x16, 0x7C
};
#endif

void * dh5_init(struct wpabuf **priv, struct wpabuf **publ)
{
#ifdef CONFIG_BK_WPS_WORKAROUND
	const struct dh_group *group = dh_groups_get(5);
	if (!group)
		return NULL;

	*priv = wpabuf_alloc(group->prime_len);
	if (*priv == NULL)
		return NULL;
	os_memcpy((*priv)->buf, g_dh_private_key, group->prime_len);

	*publ = wpabuf_alloc(group->prime_len);
	if (!publ) {
		wpabuf_clear_free(*priv);
		*priv = NULL;
		return NULL;
	}
	os_memcpy((*publ)->buf, g_dh_public_key, group->prime_len);

	wpabuf_put(*priv, group->prime_len);
	wpabuf_put(*publ, group->prime_len);
	return (void *) 1;
#else /* CONFIG_BK_WPS_WORKAROUND */
	wpabuf_free(*publ);
	*publ = dh_init(dh_groups_get(5), priv);
	if (*publ == NULL)
		return NULL;
	return (void *) 1;
#endif /* CONFIG_BK_WPS_WORKAROUND */
}


void * dh5_init_fixed(const struct wpabuf *priv, const struct wpabuf *publ)
{
	return (void *) 1;
}


struct wpabuf * dh5_derive_shared(void *ctx, const struct wpabuf *peer_public,
				  const struct wpabuf *own_private)
{
	return dh_derive_shared(peer_public, own_private, dh_groups_get(5));
}


void dh5_free(void *ctx)
{
}
