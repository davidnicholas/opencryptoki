/*
 * The Initial Developer of the Original Code is International
 * Business Machines Corporation. Portions created by IBM
 * Corporation are Copyright (C) 2005 International Business
 * Machines Corporation. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the Common Public License as published by
 * IBM Corporation; either version 1 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Common Public License for more details.
 *
 * You should have received a copy of the Common Public License
 * along with this program; if not, a copy can be viewed at
 * http://www.opensource.org/licenses/cpl1.0.php.
 */

#ifndef _TPM_SPECIFIC_H_
#define _TPM_SPECIFIC_H_

CK_CHAR manuf[] = "IBM Corp.";
CK_CHAR model[] = "TPM Token";
CK_CHAR descr[] = "Token for the Trusted Platform Module";
CK_CHAR label[] = "IBM OS PKCS#11";

/* The context we'll use globally to connect to the TSP */
TSS_HCONTEXT tspContext = NULL_HCONTEXT;
/* TSP key handles */
TSS_HKEY hSRK = NULL_HKEY;
TSS_HKEY hRootKey = NULL_HKEY;
TSS_HKEY hMigRootKey = NULL_HKEY;
TSS_HKEY hMigLeafKey = NULL_HKEY;
TSS_HKEY hUserBaseKey = NULL_HKEY;
TSS_HKEY hUserLeafKey = NULL_HKEY;

/* PKCS#11 key handles */
CK_OBJECT_HANDLE ckRootKey = 0;
CK_OBJECT_HANDLE ckMigRootKey = 0;
CK_OBJECT_HANDLE ckMigLeafKey = 0;
CK_OBJECT_HANDLE ckMigAsymKey = 0;
CK_OBJECT_HANDLE ckUserBaseKey = 0;
CK_OBJECT_HANDLE ckUserLeafKey = 0;
CK_OBJECT_HANDLE ckAESKey = 0;

/* since logging in is such an intensive process, set a flag on logout,
 * so that we only have to load 1 key on a re-login
 */
int relogging_in = 0;

/* key types in the TPM token */
#define TPMTOK_ROOT_KEY		0
#define TPMTOK_MIG_ROOT_KEY	1
#define TPMTOK_MIG_LEAF_KEY	2
#define TPMTOK_USER_BASE_KEY	3
#define TPMTOK_USER_LEAF_KEY	4
#define TPMTOK_USER_KEY		5
#define TPMTOK_SO_KEY		6

/* key identifier suffixes for the PKCS#11 objects */
#define TPMTOK_ROOT_KEY_SUFFIX		"00 TPM 00 ROOT KEY"
#define TPMTOK_MIG_ROOT_KEY_SUFFIX	"MIG ROOT KEY"
#define TPMTOK_MIG_LEAF_KEY_SUFFIX	"MIG LEAF KEY"
#define TPMTOK_USER_BASE_KEY_SUFFIX	"BASE KEY"
#define TPMTOK_USER_LEAF_KEY_SUFFIX	"LEAF KEY"

/* for use in the token object storage paths, etc */
#define TPMTOK_TOKEN_NAME	tpm

/* locations to write the backup copies of the sw generated keys */
#define TPMTOK_ROOT_KEY_BACKUP_LOCATION		"/etc/pkcs11/tpm/ROOT_KEY.pem"
#define TPMTOK_MIG_ROOT_KEY_BACKUP_LOCATION	"/etc/pkcs11/tpm/MIG_ROOT_KEY.pem"
#define TPMTOK_USER_BASE_KEY_BACKUP_LOCATION	"/etc/pkcs11/tpm/TOK_OBJ/%s/%s_BASE_KEY.pem"

/* Application ID for objects created by this token */
#define TPM_APPLICATION_ID	"PKCS#11 TPM Token"

#define TPMTOK_ROOT_KEY_SUFFIX_SIZE		strlen(TPMTOK_ROOT_KEY_SUFFIX)
#define TPMTOK_MIG_ROOT_KEY_SUFFIX_SIZE		strlen(TPMTOK_MIG_ROOT_KEY_SUFFIX)
#define TPMTOK_MIG_LEAF_KEY_SUFFIX_SIZE		strlen(TPMTOK_MIG_LEAF_KEY_SUFFIX)
#define TPMTOK_USER_BASE_KEY_SUFFIX_SIZE	strlen(TPMTOK_USER_BASE_KEY_SUFFIX)
#define TPMTOK_USER_LEAF_KEY_SUFFIX_SIZE	strlen(TPMTOK_USER_LEAF_KEY_SUFFIX)

/* TPM token specific return codes */
#define CKR_KEY_NOT_FOUND	CKR_VENDOR_DEFINED + 0
#define CKR_DATA_OBJ_NOT_FOUND	CKR_VENDOR_DEFINED + 1

RSA *openssl_gen_key();
int openssl_write_key(RSA *, char *, char *);
RSA *openssl_read_key(char *, char *);
int openssl_get_modulus_and_prime(RSA *, unsigned int *, unsigned char *, unsigned int *, unsigned char *);
void LoadBlob_PRIVKEY_DIGEST(UINT16 *, BYTE *, TCPA_KEY *);
int util_create_user_dir(char *);
#endif
