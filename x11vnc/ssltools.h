#ifndef _SSLTOOLS_H
#define _SSLTOOLS_H

/* quoted scripts, edit source not this file. */


char genCA[] = 
"#!/bin/sh\n"
"\n"
"DIR=$BASE_DIR\n"
"if [ \"x$DIR\" = \"x\" ]; then\n"
"	DIR=\"$HOME/dotkjr_vnc/certs\"\n"
"	rm -rf \"$DIR\"\n"
"fi\n"
"if echo \"$DIR\" | grep '^/' > /dev/null; then\n"
"        :\n"
"else\n"
"        DIR=\"`pwd`/$DIR\"\n"
"fi\n"
"\n"
"PATH=/usr/bin:/bin:/usr/sbin:$PATH; export PATH\n"
"if [ \"x$OPENSSL\" = \"x\" ]; then\n"
"	OPENSSL=\"openssl\"\n"
"fi\n"
"\n"
"type \"$OPENSSL\" > /dev/null	|| exit 1\n"
"\n"
"if [ -f \"$DIR/CA/cacert.pem\" ]; then\n"
"	echo \"Files will be overwritten in $DIR/CA\"\n"
"	printf \"Continue? [y]/n \"\n"
"	read x\n"
"	if [ \"x$x\" = \"xn\" ]; then\n"
"		exit 1;\n"
"	fi\n"
"fi\n"
"\n"
"#mkdir -p \"$DIR/HASH\"		|| exit 1\n"
"mkdir -p \"$DIR/clients\"		|| exit 1\n"
"#mkdir -p \"$DIR/clients/HASH\"	|| exit 1\n"
"mkdir -p \"$DIR/CA/certs\"	|| exit 1\n"
"mkdir -p \"$DIR/CA/crl\"		|| exit 1\n"
"mkdir -p \"$DIR/CA/newcerts\"	|| exit 1\n"
"mkdir -p \"$DIR/CA/private\"	|| exit 1\n"
"chmod go-rwx \"$DIR/CA/private\"	|| exit 1\n"
"mkdir -p \"$DIR/tmp\"		|| exit 1\n"
"chmod go-rwx \"$DIR/tmp\"		|| exit 1\n"
"touch \"$DIR/CA/index.txt\"	|| exit 1\n"
"if [ ! -f \"$DIR/CA/serial\" ]; then\n"
"	echo \"01\" > \"$DIR/CA/serial\"	|| exit 1\n"
"fi\n"
"\n"
"cnf='\n"
"HOME			= .\n"
"RANDFILE		= $ENV::HOME/.rnd\n"
"\n"
"####################################################################\n"
"[ ca ]\n"
"default_ca	= CA_default		# The default ca section\n"
"\n"
"####################################################################\n"
"[ CA_default ]\n"
"\n"
"dir		= ./CA			# Where everything is kept\n"
"certs		= $dir/certs		# Where the issued certs are kept\n"
"crl_dir		= $dir/crl		# Where the issued crl are kept\n"
"database	= $dir/index.txt	# database index file.\n"
"new_certs_dir	= $dir/newcerts		# default place for new certs.\n"
"certificate	= $dir/cacert.pem 	# The CA certificate\n"
"serial		= $dir/serial 		# The current serial number\n"
"crl		= $dir/crl.pem 		# The current CRL\n"
"private_key	= $dir/private/cakey.pem # The private key\n"
"RANDFILE	= $dir/private/.rand	# private random number file\n"
"\n"
"x509_extensions	= usr_cert		# The extentions to add to the cert\n"
"\n"
"name_opt 	= ca_default		# Subject Name options\n"
"cert_opt 	= ca_default		# Certificate field options\n"
"\n"
"default_days	= 365			# how long to certify for\n"
"default_crl_days= 30			# how long before next CRL\n"
"default_md	= md5			# which md to use.\n"
"preserve	= no			# keep passed DN ordering\n"
"\n"
"policy		= policy_match\n"
"\n"
"# For the CA policy\n"
"[ policy_match ]\n"
"countryName		= match\n"
"stateOrProvinceName	= match\n"
"organizationName	= match\n"
"organizationalUnitName	= optional\n"
"commonName		= supplied\n"
"emailAddress		= optional\n"
"\n"
"[ policy_anything ]\n"
"countryName		= optional\n"
"stateOrProvinceName	= optional\n"
"localityName		= optional\n"
"organizationName	= optional\n"
"organizationalUnitName	= optional\n"
"commonName		= supplied\n"
"emailAddress		= optional\n"
"\n"
"####################################################################\n"
"[ req ]\n"
"default_bits		= 2048\n"
"default_keyfile 	= privkey.pem\n"
"distinguished_name	= req_distinguished_name\n"
"attributes		= req_attributes\n"
"x509_extensions	= v3_ca	# The extentions to add to the self signed cert\n"
"\n"
"string_mask = nombstr\n"
"\n"
"# req_extensions = v3_req # The extensions to add to a certificate request\n"
"\n"
"[ req_distinguished_name ]\n"
"countryName			= Country Name (2 letter code)\n"
"countryName_default		= AU\n"
"countryName_min			= 2\n"
"countryName_max			= 2\n"
"\n"
"stateOrProvinceName		= State or Province Name (full name)\n"
"stateOrProvinceName_default	= mystate\n"
"\n"
"localityName			= Locality Name (eg, city)\n"
"\n"
"0.organizationName		= Organization Name (eg, company)\n"
"0.organizationName_default	= x11vnc server CA\n"
"\n"
"organizationalUnitName		= Organizational Unit Name (eg, section)\n"
"\n"
"commonName			= Common Name (eg, YOUR name)\n"
"commonName_default		= %USER x11vnc server CA\n"
"commonName_max			= 64\n"
"\n"
"emailAddress			= Email Address\n"
"emailAddress_default		= x11vnc@CA.nowhere\n"
"emailAddress_max		= 64\n"
"\n"
"[ req_attributes ]\n"
"challengePassword		= A challenge password\n"
"challengePassword_min		= 4\n"
"challengePassword_max		= 20\n"
"\n"
"unstructuredName		= An optional company name\n"
"\n"
"[ usr_cert ]\n"
"\n"
"basicConstraints=CA:FALSE\n"
"\n"
"nsComment			= \"OpenSSL Generated Certificate\"\n"
"\n"
"subjectKeyIdentifier=hash\n"
"authorityKeyIdentifier=keyid,issuer:always\n"
"\n"
"[ v3_req ]\n"
"\n"
"basicConstraints = CA:FALSE\n"
"keyUsage = nonRepudiation, digitalSignature, keyEncipherment\n"
"\n"
"[ v3_ca ]\n"
"\n"
"subjectKeyIdentifier=hash\n"
"\n"
"authorityKeyIdentifier=keyid:always,issuer:always\n"
"\n"
"basicConstraints = CA:true\n"
"\n"
"[ crl_ext ]\n"
"\n"
"authorityKeyIdentifier=keyid:always,issuer:always\n"
"\n"
"'\n"
"selfcnf='\n"
"####################################################################\n"
"[ req ]\n"
"default_bits		= 2048\n"
"encrypt_key		= yes\n"
"distinguished_name	= req_distinguished_name\n"
"x509_extensions		= cert_type\n"
"\n"
"[ req_distinguished_name ]\n"
"countryName			= Country Name (2 letter code)\n"
"countryName_default		= AU\n"
"countryName_min			= 2\n"
"countryName_max			= 2\n"
"\n"
"stateOrProvinceName		= State or Province Name (full name)\n"
"stateOrProvinceName_default	= mystate\n"
"\n"
"localityName			= Locality Name (eg, city)\n"
"\n"
"0.organizationName		= Organization Name (eg, company)\n"
"0.organizationName_default	= x11vnc server self-signed\n"
"\n"
"organizationalUnitName		= Organizational Unit Name (eg, section)\n"
"\n"
"commonName			= Common Name (eg, YOUR name)\n"
"commonName_default		= x11vnc server self-signed %NAME\n"
"commonName_max			= 64\n"
"\n"
"emailAddress			= Email Address\n"
"emailAddress_default		= x11vnc@self-signed.nowhere\n"
"emailAddress_max		= 64\n"
"\n"
"[ cert_type ]\n"
"nsCertType = server\n"
"\n"
"'\n"
"echo \"$cnf\" | sed -e \"s/%USER/$USER/\" \\\n"
"	> \"$DIR/CA/ssl.cnf\" || exit 1\n"
"echo \"$cnf\" | sed -e \"s/%USER *//\" -e 's/server CA/server %NAME/g' -e 's/@CA/@server/' \\\n"
"	> \"$DIR/CA/ssl.cnf.server\" || exit 1\n"
"echo \"$cnf\" | sed -e \"s/%USER *//\" -e 's/server CA/client %NAME/g' -e 's/@CA/@client/' \\\n"
"	> \"$DIR/CA/ssl.cnf.client\" || exit 1\n"
"\n"
"echo \"$selfcnf\" > \"$DIR/CA/self.cnf.server\" || exit 1\n"
"echo \"$selfcnf\" | sed -e 's/ server/ client/g' \\\n"
"	> \"$DIR/CA/self.cnf.client\" || exit 1\n"
"\n"
"cd \"$DIR\"	|| exit 1\n"
"\n"
"echo \"\"\n"
"echo \"----------------------------------------------------------------------\"\n"
"echo \"Generating your x11vnc CA (certificate authority) key and certificate:\"\n"
"echo \"\"\n"
"echo \"Please supply a passphrase and any other information you care to.\"\n"
"echo \"----------------------------------------------------------------------\"\n"
"echo \"\"\n"
"\n"
"\"$OPENSSL\" req -config \"$DIR/CA/ssl.cnf\" -new -x509 \\\n"
"	-keyout \"$DIR/CA/private/cakey.pem\" \\\n"
"	-out \"$DIR/CA/cacert.pem\"\n"
"\n"
"chmod go-rwx \"$DIR/CA/private/cakey.pem\"\n"
"\n"
"if [ $? != 0 ]; then\n"
"	echo \"openssl failed.\"\n"
"	exit 1\n"
"fi\n"
"\n"
"echo \"\"\n"
"echo \"----------------------------------------------------------------------\"\n"
"echo \"Your public x11vnc CA cert is:\"\n"
"echo \"\"\n"
"echo \"        $DIR/CA/cacert.pem\"\n"
"echo \"\"\n"
"echo \"   It may be copied to other applications, e.g. Web browser, Java\"\n"
"echo \"   Applet keystore, or stunnel cfg, to use to verify signed server\"\n"
"echo \"   or client certs, etc.\"\n"
"echo \"\"\n"
"echo \"Your private x11vnc CA key is:\"\n"
"echo \"\"\n"
"echo \"        $DIR/CA/private/cakey.pem\"\n"
"echo \"\"\n"
"echo \"   It will be used to sign server or client certs, keep it secret.\"\n"
"echo \"----------------------------------------------------------------------\"\n"
"echo \"\"\n"
"printf \"Press Enter to print the cacert.pem certificate to the screen: \"\n"
"read x\n"
"echo \"\"\n"
"cat \"$DIR/CA/cacert.pem\"\n"
;

char genCert[] = 
"#!/bin/sh\n"
"\n"
"direrror() {\n"
"	echo \"\"\n"
"	echo \"You need first to run:\"\n"
"	echo \"\"\n"
"	if echo \"$DIR\" | grep '/\\.vnc/certs' > /dev/null; then\n"
"		echo \"	x11vnc -sslGenCA\"\n"
"	else\n"
"		echo \"	x11vnc -sslGenCA $DIR\"\n"
"	fi\n"
"	echo \"\"\n"
"	echo \"to create the CA cert file and other needed config files and directories.\"\n"
"	echo \"\"\n"
"	echo \"Then you can run: x11vnc -sslGenCert $type $name0\"\n"
"	echo \"\"\n"
"	if [ \"X$1\" != \"X\" ]; then\n"
"		echo \"(missing file/dir: $1)\"\n"
"		echo \"\"\n"
"	fi\n"
"	exit 1\n"
"}\n"
"\n"
"make_HASH() {\n"
"	crt=\"$1\"\n"
"	remove=\"$2\"\n"
"	if [ ! -f \"$crt\" ]; then\n"
"		return\n"
"	fi\n"
"	dirhash=`dirname \"$crt\"`/HASH\n"
"	bashash=`basename \"$crt\"`\n"
"	if [ ! -d \"$dirhash\" ]; then\n"
"		return\n"
"	fi\n"
"	hash=`\"$OPENSSL\" x509 -hash -noout -in \"$crt\" 2>/dev/null | head -1`\n"
"	if [ \"X$hash\" != \"X\" ]; then\n"
"		for i in 0 1 2 3 4 5 6 7 8 9\n"
"		do\n"
"			lnk=\"$dirhash/$hash.$i\"\n"
"			if [ \"X$remove\" = \"X1\" ]; then\n"
"				if [ -h \"$lnk\" ]; then\n"
"					if cmp \"$lnk\" \"$crt\" > /dev/null 2>&1; then\n"
"						ls -l \"$lnk\"\n"
"						rm -i \"$lnk\"\n"
"					fi\n"
"				fi\n"
"			else\n"
"				if [ -h \"$lnk\" ]; then\n"
"					if [ ! -f \"$lnk\" ]; then\n"
"						rm -f \"$lnk\" 1>/dev/null 2>&1\n"
"					else\n"
"						continue\n"
"					fi\n"
"				fi\n"
"				if [ \"x$HASH_verbose\" = \"x1\" ]; then\n"
"					echo \"creating: $lnk -> ../$bashash\"\n"
"				fi\n"
"				ln -s \"../$bashash\" \"$lnk\"\n"
"				break\n"
"			fi\n"
"		done\n"
"	fi\n"
"}\n"
"\n"
"create_key() {\n"
"	\n"
"	echo \"----------------------------------------------------------------------\"\n"
"	echo \"Creating new x11vnc certificate and key for name: $type $name0\"\n"
"	echo \"\"\n"
"\n"
"	cnf=\"$DIR/tmp/cnf.$$\"\n"
"	trap \"rm -f \\\"$cnf\\\"\" 0 1 2 15\n"
"\n"
"	rm -f \"$DIR/$dest.key\" \"$DIR/$dest.crt\" \"$DIR/$dest.req\"\n"
"\n"
"	if [ \"x$self\" = \"x1\" ]; then\n"
"		if [ ! -f \"$DIR/CA/self.cnf.$type\" ]; then\n"
"			direrror \"$DIR/CA/self.cnf.$type\"\n"
"		fi\n"
"		cat \"$DIR/CA/self.cnf.$type\" | sed -e \"s/%NAME/$name0/\" > \"$cnf\" || exit 1\n"
"		\"$OPENSSL\" req -config \"$cnf\" -nodes -new -newkey rsa:2048 -x509 $REQ_ARGS \\\n"
"			-keyout \"$DIR/$dest.key\" \\\n"
"			-out    \"$DIR/$dest.crt\"\n"
"	else\n"
"		if [ ! -f \"$DIR/CA/ssl.cnf.$type\" ]; then\n"
"			direrror \"$DIR/CA/ssl.cnf.$type\"\n"
"		fi\n"
"		cat \"$DIR/CA/ssl.cnf.$type\" | sed  -e \"s/%NAME/$name0/\" > \"$cnf\" || exit 1\n"
"		\"$OPENSSL\" req -config \"$cnf\" -nodes -new -newkey rsa:2048 $REQ_ARGS \\\n"
"			-keyout \"$DIR/$dest.key\" \\\n"
"			-out    \"$DIR/$dest.req\"\n"
"	fi\n"
"	rc=$?\n"
"	if [ -f \"$DIR/$dest.key\" ]; then\n"
"		chmod go-rwx \"$DIR/$dest.key\"\n"
"	fi\n"
"\n"
"\n"
"\n"
"	if [ $rc != 0 ]; then\n"
"		echo \"openssl 'req' command failed\"\n"
"		rm -f \"$DIR/$dest.key\" \"$DIR/$dest.crt\" \"$DIR/$dest.req\"\n"
"		exit 1\n"
"	fi\n"
"}\n"
"\n"
"enc_key() {\n"
"	\n"
"	echo \"\"\n"
"	echo \"----------------------------------------------------------------------\"\n"
"	echo \"Do you want to protect the generated private key with a passphrase?\"\n"
"	echo \"Doing so will significantly decrease the chances someone could steal\"\n"
"	if [ \"x$type\" = \"xserver\" ]; then\n"
"	echo \"the key and pretend to be your x11vnc server.  The downside is it is\"\n"
"	else\n"
"	echo \"the key and pretend to be your VNC client.  The downside is it is\"\n"
"	fi\n"
"	echo \"inconvenient because you will have to supply the passphrase every\"\n"
"	if [ \"x$type\" = \"xserver\" ]; then\n"
"	echo \"time you start x11vnc using this key.\"\n"
"	else\n"
"	echo \"time you start the VNC viewer SSL tunnel using this key.\"\n"
"	fi\n"
"	echo \"\"\n"
"	printf \"Protect key with a passphrase?  [y]/n \"\n"
"	read x\n"
"	estr=\" *unencrypted*\"\n"
"	if [ \"x$ENCRYPT_ONLY\" != \"x\" ]; then\n"
"		target=\"$ENCRYPT_ONLY\"\n"
"	else\n"
"		target=\"$DIR/$dest.key\"\n"
"		bdir=`dirname \"$DIR/$dest.key\"`\n"
"		if [ ! -d \"$bdir\" ]; then\n"
"			direrror \"$bdir\"\n"
"		fi\n"
"	fi\n"
"	if [ \"x$x\" != \"xn\" ]; then\n"
"		\"$OPENSSL\" rsa -in \"$target\" -des3 -out \"$target\"\n"
"		if [ $? != 0 ]; then\n"
"			echo \"openssl 'rsa' command failed\"\n"
"			rm -f \"$DIR/$dest.key\" \"$DIR/$dest.crt\" \"$DIR/$dest.req\"\n"
"			exit 1\n"
"		fi\n"
"		estr=\" encrypted\"\n"
"	fi\n"
"	echo \"\"\n"
"}\n"
"\n"
"sign_key() {\n"
"	cd \"$DIR\" || exit 1\n"
"\n"
"	if [ \"x$self\" = \"x1\" ]; then\n"
"		:\n"
"	else\n"
"		if echo \"$name0\" | grep '^req:' > /dev/null; then\n"
"			echo \"\"\n"
"			echo \"----------------------------------------------------------------------\"\n"
"			echo \"Your x11vnc $type certificate request is:\"\n"
"			echo \"\"\n"
"			echo \"        $DIR/$dest.req\"\n"
"			echo \"\"\n"
"			echo \"   It may be sent to an external CA for signing, afterward you can\"\n"
"			echo \"   save the cert they send you in:\"\n"
"			echo \"\"\n"
"			echo \"        $DIR/$dest.crt\"\n"
"			echo \"\"\n"
"			echo \"Your$estr private x11vnc $type key is:\"\n"
"			echo \"\"\n"
"			echo \"        $DIR/$dest.key\"\n"
"			echo \"\"\n"
"			echo \"   You should combine it and the received cert in the file:\"\n"
"			echo \"\"\n"
"			echo \"        $DIR/$dest.pem\"\n"
"			echo \"\"\n"
"			echo \"   It will be needed by applications to identify themselves.\"\n"
"			echo \"   This file should be kept secret.\"\n"
"			echo \"----------------------------------------------------------------------\"\n"
"			echo \"\"\n"
"			printf \"Press Enter to print the $dest.req cert request to the screen: \"\n"
"			read x\n"
"			echo \"\"\n"
"			cat \"$DIR/$dest.req\"\n"
"			exit 0\n"
"		fi\n"
"		echo \"\"\n"
"		echo \"\"\n"
"		echo \"----------------------------------------------------------------------\"\n"
"		echo \"Now signing the new key with CA private key.  You will need to supply\"\n"
"		echo \"the CA key passphrase and reply \\\"y\\\" to sign and commit the key.\"\n"
"		echo \"\"\n"
"		\"$OPENSSL\" ca -config \"$cnf\" -policy policy_anything -notext \\\n"
"			-in  \"$DIR/$dest.req\" \\\n"
"			-out \"$DIR/$dest.crt\"\n"
"		if [ $? != 0 ]; then\n"
"			echo \"\"\n"
"			echo \"openssl 'ca' command failed\"\n"
"			echo \"\"\n"
"			echo \"  You may have a duplicate DN entry for this name in:\"\n"
"			echo \"\"\n"
"			echo \"          $DIR/CA/index.txt\"\n"
"			echo \"\"\n"
"			echo \"  remove the duplicate in that file and try again.\"\n"
"			echo \"\"\n"
"			rm -f \"$DIR/$dest.key\" \"$DIR/$dest.crt\" \"$DIR/$dest.req\"\n"
"			exit 1\n"
"		fi\n"
"	fi\n"
"\n"
"	cat  \"$DIR/$dest.key\"  \"$DIR/$dest.crt\" \\\n"
"		> \"$DIR/$dest.pem\" || exit 1 \n"
"\n"
"	make_HASH \"$DIR/$dest.crt\" 0\n"
"\n"
"	rm -f \"$DIR/$dest.key\" \"$DIR/$dest.req\" || exit 1\n"
"	chmod go-rwx \"$DIR/$dest.pem\" || exit 1\n"
"\n"
"	if [ \"x$type\" = \"xserver\" -o \"x$type\" = \"xclient\" ]; then\n"
"		echo \"\"\n"
"		echo \"----------------------------------------------------------------------\"\n"
"		echo \"Your public x11vnc $type cert is:\"\n"
"		echo \"\"\n"
"		echo \"        $DIR/$dest.crt\"\n"
"		echo \"\"\n"
"		echo \"   It may be copied to other machines / applications to be used for\"\n"
"		echo \"   authentication.  However, since it is signed with the x11vnc CA\"\n"
"		echo \"   key, all the applications need is the x11vnc CA certificate.\"\n"
"		echo \"\"\n"
"		echo \"Your$estr private x11vnc $type key is:\"\n"
"		echo \"\"\n"
"		echo \"        $DIR/$dest.pem\"\n"
"		echo \"\"\n"
"		echo \"   It will be needed by applications to identify themselves.\"\n"
"		echo \"   This file should be kept secret.\"\n"
"		echo \"----------------------------------------------------------------------\"\n"
"		echo \"\"\n"
"	fi\n"
"\n"
"	printf \"Press Enter to print the $dest.crt certificate to the screen: \"\n"
"	read x\n"
"	echo \"\"\n"
"	cat \"$DIR/$dest.crt\"\n"
"}\n"
"\n"
"DIR=$BASE_DIR\n"
"if [ \"x$DIR\" = \"x\" ]; then\n"
"        DIR=\"$HOME/dotkjr_vnc/certs\"\n"
"fi\n"
"if echo \"$DIR\" | grep '^/' > /dev/null; then\n"
"	:\n"
"else\n"
"	DIR=\"`pwd`/$DIR\"\n"
"fi\n"
"\n"
"if [ \"x$HASHON\" != \"x\" ]; then\n"
"	for dir in \"$DIR/HASH\" \"$DIR/clients/HASH\"\n"
"	do\n"
"		if [ -d \"$dir\" ]; then\n"
"			rm -rf \"$dir\"\n"
"		fi\n"
"	done\n"
"	dir=\"$DIR/HASH\"\n"
"	mkdir -p \"$dir\" || exit 1\n"
"	dir=\"$DIR/clients/HASH\"\n"
"	mkdir -p \"$dir\" || exit 1\n"
"	HASH_verbose=1\n"
"	for f in \"$DIR\"/*.crt \"$DIR\"/clients/*.crt\n"
"	do\n"
"		if [ -f \"$f\" ]; then\n"
"			make_HASH \"$f\" 0\n"
"		fi\n"
"	done\n"
"	exit\n"
"fi\n"
"if [ \"x$HASHOFF\" != \"x\" ]; then\n"
"	dir=\"$DIR/HASH\"\n"
"	for dir in \"$DIR/HASH\" \"$DIR/clients/HASH\"\n"
"	do\n"
"		if [ -d \"$dir\" ]; then\n"
"			for f in \"$dir\"/*\n"
"			do\n"
"				if [ -f \"$f\" ]; then\n"
"					echo \"deleting: $f\"\n"
"					rm -f \"$f\"\n"
"				fi\n"
"			done\n"
"			rm -rf \"$dir\"\n"
"		fi\n"
"	done\n"
"	exit\n"
"fi\n"
"\n"
"PATH=/usr/bin:/bin:/usr/sbin:$PATH; export PATH\n"
"if [ \"x$OPENSSL\" = \"x\" ]; then\n"
"        OPENSSL=\"openssl\"\n"
"fi\n"
"\n"
"type \"$OPENSSL\" > /dev/null	|| exit 1\n"
"\n"
"self=\"\"\n"
"if [ \"x$SELF\" != \"x\" ]; then\n"
"	self=1\n"
"elif [ \"x$1\" = \"x-self\" ]; then\n"
"	shift\n"
"	self=1\n"
"fi\n"
"\n"
"if [ \"x$TYPE\" != \"x\" ]; then\n"
"	type=\"$TYPE\"\n"
"else\n"
"	if [ \"X$1\" != \"X\" ]; then\n"
"		type=\"$1\"\n"
"		shift\n"
"	fi\n"
"fi\n"
"if [ \"x$NAME\" != \"x\" ]; then\n"
"	name=\"$NAME\"\n"
"else\n"
"	if [ \"X$1\" != \"X\" ]; then\n"
"		name=\"$1\"\n"
"		shift\n"
"	fi\n"
"fi\n"
"\n"
"if echo \"$name\" | grep '^self:' > /dev/null; then\n"
"	self=1\n"
"fi\n"
"\n"
"if [ \"x$type\" = \"xserver\" ]; then\n"
"	name0=\"$name\"\n"
"	if echo \"$name\" | grep '^-' > /dev/null; then\n"
"		:\n"
"	elif [ \"x$name\" != \"x\" ]; then\n"
"		name=\"-$name\";\n"
"	fi\n"
"	dest=\"server$name\"\n"
"elif [ \"x$type\" = \"xclient\" ]; then\n"
"	if [ \"x$name\" = \"x\" ]; then\n"
"		name=\"nobody\"\n"
"	fi\n"
"	name0=\"$name\"\n"
"	dest=\"clients/$name\"\n"
"else\n"
"	exit 1\n"
"fi\n"
"\n"
"#set -xv\n"
"\n"
"if [ \"x$INFO_ONLY\" != \"x\" ]; then\n"
"	echo \"\"\n"
"	echo \"VNC Certificate file:\"\n"
"	echo \"	$INFO_ONLY\"\n"
"	echo \"\"\n"
"	\"$OPENSSL\" x509 -text -in \"$INFO_ONLY\"\n"
"	exit \n"
"elif [ \"x$DELETE_ONLY\" != \"x\" ]; then\n"
"	echo \"\"\n"
"	echo \"VNC Certificate file:\"\n"
"	echo \"	$DELETE_ONLY\"\n"
"	echo \"\"\n"
"	\n"
"	base=`echo \"$DELETE_ONLY\" | sed -e 's/\\....$//'`\n"
"	for suff in crt pem key req\n"
"	do\n"
"		try=\"$base.$suff\"\n"
"		if [ -f \"$try\" ]; then\n"
"			make_HASH \"$try\" 1\n"
"			rm -i \"$try\"\n"
"		fi\n"
"	done\n"
"	if echo \"$base\" | grep 'CA/cacert$' > /dev/null; then\n"
"		base2=`echo \"$base\" | sed -e 's,cacert$,private/cakey,'`\n"
"	else\n"
"		echo \"\"\n"
"		exit\n"
"	fi\n"
"	echo \"\"\n"
"	for suff in crt pem key req\n"
"	do\n"
"		try=\"$base2.$suff\"\n"
"		if [ -f \"$try\" ]; then\n"
"			make_HASH \"$try\" 1\n"
"			rm -i \"$try\"\n"
"		fi\n"
"	done\n"
"	echo \"\"\n"
"	exit \n"
"elif [ \"x$ENCRYPT_ONLY\" != \"x\" ]; then\n"
"	if [ \"x$type\" = \"x\" ]; then\n"
"		type=\"server\"\n"
"	fi\n"
"	echo \"\"\n"
"	echo \"Key PEM file:\"\n"
"	echo \"	$ENCRYPT_ONLY\"\n"
"	enc_key\n"
"	exit\n"
"fi\n"
"\n"
"if [ ! -d \"$DIR/tmp\" ]; then\n"
"	direrror \"$DIR/tmp\"\n"
"fi\n"
"bdir=`dirname \"$DIR/$dest.key\"`\n"
"if [ ! -d \"$bdir\" ]; then\n"
"	direrror \"$bdir\"\n"
"fi\n"
"if [ ! -f \"$DIR/CA/cacert.pem\" ]; then\n"
"	direrror \"$DIR/CA/cacert.pem\"\n"
"fi\n"
"\n"
"create_key\n"
"enc_key\n"
"sign_key\n"
;

char find_display[] = 
"#!/bin/sh\n"
"#\n"
"# Script for use in -display WAIT:cmd=FINDDISPLAY -unixpw mode.\n"
"# Attempts to find 1) DISPLAY and 2) XAUTH data for the user and\n"
"# returns them to caller.\n"
"#\n"
"# The idea is this script is run via su - user -c ... and returns\n"
"# display + xauth info to caller (x11vnc running as root or nobody).\n"
"# x11vnc then uses the info to open the display.\n"
"#\n"
"\n"
"#FIND_DISPLAY_OUTPUT=/tmp/fdo.$USER.txt\n"
"if [ \"X$FIND_DISPLAY_OUTPUT\" != \"X\" ]; then\n"
"	if [ \"X$FIND_DISPLAY_EXEC\" = \"X\" ]; then\n"
"		FIND_DISPLAY_EXEC=1\n"
"		export FIND_DISPLAY_EXEC\n"
"		if [ \"X$FIND_DISPLAY_OUTPUT\" != \"X\" ]; then\n"
"			/bin/sh $0 \"$@\" 2> $FIND_DISPLAY_OUTPUT\n"
"		else\n"
"			/bin/sh $0 \"$@\" 2> /dev/null\n"
"		fi\n"
"		exit $?\n"
"	fi\n"
"fi\n"
"\n"
"if [ \"X$FIND_DISPLAY_OUTPUT\" != \"X\" ]; then\n"
"	set -xv\n"
"fi\n"
"\n"
"#env; set -xv\n"
"PATH=$PATH:/bin:/usr/bin:/usr/X11R6/bin:/usr/bin/X11:/usr/openwin/bin:/usr/ucb\n"
"export PATH\n"
"\n"
"# -n means no xauth, -f prescribes file to use.\n"
"showxauth=1\n"
"if [ \"X$1\" = \"X-n\" ]; then\n"
"	showxauth=\"\"\n"
"	shift\n"
"fi\n"
"if [ \"X$1\" = \"X-f\" ]; then\n"
"	shift\n"
"	if [ ! -r $1 ]; then\n"
"		echo \"\"\n"
"		exit 1\n"
"	fi\n"
"	export XAUTHORITY=\"$1\"\n"
"	shift\n"
"fi\n"
"\n"
"user=\"$1\"			# cmd line arg takes precedence\n"
"if [ \"X$user\" = \"X\" ]; then\n"
"	user=$X11VNC_USER	# then X11VNC_USER\n"
"fi\n"
"if [ \"X$user\" = \"X\" ]; then\n"
"	user=$USER		# then USER\n"
"fi\n"
"if [ \"X$user\" = \"X\" ]; then\n"
"	user=$LOGNAME		# then LOGNAME\n"
"fi\n"
"if [ \"X$user\" = \"X\" ]; then\n"
"	user=`whoami 2>/dev/null`	# desperation whoami\n"
"fi\n"
"if [ \"X$user\" = \"X\" ]; then\n"
"	echo \"\"		# failure\n"
"	exit 1\n"
"fi\n"
"\n"
"# Now try to match X DISPLAY to user:\n"
"\n"
"# who(1) output column 2:\n"
"#gone=`last $user | grep 'gone.*no.logout' | awk '{print $2}' | grep '^:' | sed -e 's,/.*,,' | tr '\\n' '|'`\n"
"#gone=\"${gone}__quite_impossible__\"\n"
"#display=`who | grep \"^${user}[ 	][ 	]*:[0-9]\" | egrep -v \" ($gone)\\>\" | head -1 \\\n"
"#    | awk '{print $2}' | sed -e 's,/.*$,,'`\n"
"poss=\"\"\n"
"list=`who | grep \"^${user}[ 	][ 	]*:[0-9]\" | awk '{print $2}' | sed -e 's,/.*$,,'`\n"
"list=\"$list \"`w -h \"$user\" | grep \"^${user}[ 	][ 	]*:[0-9]\" | awk '{print $2}' | sed -e 's,/.*$,,'`\n"
"list=\"$list \"`who | grep \"^${user}[ 	]\" | awk '{print $NF}' | grep '(:[0-9]' | sed -e 's/[()]//g'`\n"
"host=`hostname | sed -e 's/\\..*$//'`\n"
"if [ \"X$X11VNC_FINDDISPLAY_SKIP_XAUTH\" = \"X\" ]; then\n"
"	list=\"$list \"`xauth list | awk '{print $1}' | grep /unix | grep \"^${host}\" | sed -e 's/^.*:/:/' | sort -n | uniq`\n"
"fi\n"
"uname=`uname`\n"
"nsout=`netstat -an`\n"
"psout=`ps -ef`\n"
"for p in $list\n"
"do\n"
"	d=`echo \"$p\" | sed -e 's/://' -e 's/\\..*$//'`\n"
"	ok=\"\"\n"
"	if [ \"X$X11VNC_SKIP_DISPLAY\" != \"X\" ]; then\n"
"		mat=\"\"\n"
"		for skip in `echo $X11VNC_SKIP_DISPLAY | tr ',' '\\n'`\n"
"		do\n"
"			if echo \"$skip\" | grep \"^:\" > /dev/null; then\n"
"				:\n"
"			else\n"
"				skip=\":$skip\"\n"
"			fi\n"
"			if echo \"$skip\" | grep \":$d\\>\" > /dev/null; then\n"
"				mat=1\n"
"				break\n"
"				\n"
"			fi\n"
"		done\n"
"		if [ \"X$mat\" = \"X1\" ]; then\n"
"			continue\n"
"		fi\n"
"	fi\n"
"	xd=\"/tmp/.X11-unix/X$d\"\n"
"	if [ -r \"$xd\" -o -w \"$xd\" -o -x \"$xd\" ]; then\n"
"		if echo \"$nsout\" | grep \"/tmp/.X11-unix/X$d[  ]*\\$\" > /dev/null; then\n"
"			ok=1\n"
"		fi\n"
"	fi\n"
"	if [ \"X$ok\" = \"X\" ]; then\n"
"		if [ -f \"/tmp/.X$d-lock\" ]; then\n"
"			pid=`cat \"/tmp/.X$d-lock\" | sed -e 's/[ 	]//g'`\n"
"			if echo \"$pid\" | grep '^[0-9][0-9]*$' > /dev/null; then\n"
"				if [ \"X$uname\" = \"XLinux\" -o \"X$uname\" = \"XSunOS\" ]; then\n"
"					if [ -d \"/proc/$pid\" ]; then\n"
"						ok=1\n"
"					fi\n"
"				elif echo \"$ps_out\" | awk '{print $2}' | grep -w \"$pid\" > /dev/null; then\n"
"					ok=1\n"
"				fi\n"
"			fi\n"
"		fi\n"
"	fi\n"
"	if [ \"X$ok\" = \"X1\" ]; then\n"
"		poss=\"$poss $p\"\n"
"	fi\n"
"done\n"
"\n"
"poss=`echo \"$poss\" | sed -e 's/^ *//' -e 's/ *$//'`\n"
"\n"
"if [ \"X$X11VNC_FINDDISPLAY_SKIP_XAUTH\" != \"X\" ]; then\n"
"	display=`echo \"$poss\" | tr ' ' '\\n' | head -1`\n"
"else\n"
"	freebie=\"\"\n"
"	for p in $poss\n"
"	do\n"
"		xdpyinfo -display \"$p\" >/dev/null 2>&1\n"
"		if [ $? = 0 ]; then\n"
"			# try again with no authority:\n"
"			env XAUTHORITY=/dev/null xdpyinfo -display \"$p\" >/dev/null 2>&1\n"
"			# 0 means got in for free... skip it.\n"
"			if [ $? != 0 ]; then\n"
"				# keep it\n"
"				display=\"$p\"\n"
"				break\n"
"			else\n"
"				if [ \"X$freebie\" = \"X\" ]; then\n"
"					freebie=\"$p\"\n"
"				fi\n"
"			fi\n"
"		fi\n"
"	done\n"
"	if [ \"X$display\" = \"X\" -a \"X$freebie\" != \"X\" ]; then\n"
"		display=\"$freebie\"\n"
"	fi\n"
"fi\n"
"\n"
"if [ \"X$display\" = \"X\" ]; then\n"
"	echo \"\"		# failure\n"
"	exit 1\n"
"fi\n"
"\n"
"chvt=\"\"\n"
"if [ \"X$uname\" = \"XLinux\" ]; then\n"
"	d2=$display\n"
"	d3=`echo \"$d2\" | sed -e 's/^.*:/:/' -e 's/\\..*$//'`\n"
"	d4=\"($d2|$d3)\"\n"
"	vt=`ps wwwwwaux | grep X | egrep -v 'startx|xinit' | egrep \" $d4 \" | egrep ' vt([789]|[1-9][0-9][0-9]*) ' | grep -v grep | head -1`\n"
"	if [ \"X$vt\" != \"X\" ]; then\n"
"		vt=`echo \"$vt\" | sed -e 's/^.* vt\\([0-9][0-9]*\\) .*$/\\1/'`\n"
"		if echo \"$vt\" | grep '^[0-9][0-9]*$' > /dev/null; then\n"
"			chvt=\",VT=$vt\"\n"
"		fi\n"
"	else\n"
"		vt=`ps wwwwwaux | grep X | egrep \" $d4 \" | egrep ' tty([789]|[1-9][0-9][0-9]*) ' | grep -v grep | head -1`\n"
"		if [ \"X$vt\" != \"X\" ]; then\n"
"			vt=`echo \"$vt\" | sed -e 's/^.* tty\\([0-9][0-9]*\\) .*$/\\1/'`\n"
"			if echo \"$vt\" | grep '^[0-9][0-9]*$' > /dev/null; then\n"
"				chvt=\",VT=$vt\"\n"
"			fi\n"
"		else\n"
"			pvt=`ps wwwwwaux | grep X | egrep -v 'startx|xinit' | egrep \" $d4 \" | head -1 | awk '{print $2}'`\n"
"			if [ \"X$pvt\" != \"X\" ]; then\n"
"				vt=`lsof -p \"$pvt\" | egrep '/dev/tty([789]|[1-9][0-9][0-9]*)$' | grep -v grep | head -1 | awk '{print $NF}' | sed -e 's,/dev/tty,,'`\n"
"				if echo \"$vt\" | grep '^[0-9][0-9]*$' > /dev/null; then\n"
"					chvt=\",VT=$vt\"\n"
"				else\n"
"					chvt=\",XPID=$pvt\"\n"
"				fi\n"
"			fi\n"
"		fi\n"
"	fi\n"
"fi\n"
"\n"
"echo \"DISPLAY=$display$chvt\"\n"
"if [ \"X$showxauth\" != \"X\" ]; then\n"
"	xauth extract - \"$display\" 2>/dev/null\n"
"fi\n"
"\n"
"exit 0\n"
;

char create_display[] = 
"#!/bin/sh\n"
"\n"
"#CREATE_DISPLAY_OUTPUT=/tmp/cdo.txt\n"
"\n"
"CREATE_DISPLAY_OUTPUT=/tmp/cdo.$USER.txt\n"
"if [ \"X$CREATE_DISPLAY_OUTPUT\" != \"X\" ]; then\n"
"	if [ \"X$CREATE_DISPLAY_EXEC\" = \"X\" ]; then\n"
"		CREATE_DISPLAY_EXEC=1\n"
"		export CREATE_DISPLAY_EXEC\n"
"		if [ \"X$CREATE_DISPLAY_OUTPUT\" != \"X\" ]; then\n"
"			/bin/sh $0 \"$@\" 2> $CREATE_DISPLAY_OUTPUT\n"
"		else\n"
"			/bin/sh $0 \"$@\" 2> /dev/null\n"
"		fi\n"
"		exit $?\n"
"	fi\n"
"fi\n"
"\n"
"\n"
"if [ \"X$CREATE_DISPLAY_OUTPUT\" != \"X\" ]; then\n"
"	set -xv\n"
"fi\n"
"\n"
"findfree() {\n"
"	try=20\n"
"	n=\"\"\n"
"	nsout=\"\"\n"
"	if [ \"X$have_netstat\" != \"X\" ]; then\n"
"		nsout=`$have_netstat -an`\n"
"	fi\n"
"	while [ $try -lt 99 ]\n"
"	do\n"
"		if [ ! -f \"/tmp/.X${try}-lock\" ]; then\n"
"			if echo \"$nsout\" | grep \"/tmp/.X11-unix/X${try}[ 	]*\\$\" > /dev/null; then\n"
"				:\n"
"			else\n"
"				n=$try\n"
"				break\n"
"			fi\n"
"		fi\n"
"		try=`expr $try + 1`\n"
"	done\n"
"	echo \"$n\"\n"
"}\n"
"\n"
"random() {\n"
"	if [ \"X$RANDOM\" != \"X\" ]; then\n"
"		echo \"$RANDOM\"\n"
"	else\n"
"		r1=`bash -c 'echo $RANDOM' 2>/dev/null`\n"
"		if echo \"$r1\" | grep '^[0-9][0-9]*$' > /dev/null; then\n"
"			echo \"$r1\"\n"
"		else\n"
"			r2=`sh -c 'echo $$; date; ps -elf' 2>/dev/null | sum -r 2>/dev/null | awk '{print $1}'`\n"
"			if echo \"$r2\" | grep '^[0-9][0-9]*$' > /dev/null; then\n"
"				echo \"$r2\"\n"
"			else\n"
"				r3=`sh -c 'echo $$'`\n"
"				echo \"$r3\"\n"
"			fi\n"
"		fi\n"
"	fi\n"
"}\n"
"\n"
"findsession() {\n"
"	if [ \"X$session\" != \"X\" ]; then\n"
"		echo \"$session\"\n"
"		return\n"
"	fi\n"
"	if [ \"X$have_gnome_session\" != \"X\" -a \"X$FD_SESS\" = \"Xgnome\" ]; then\n"
"		echo \"$have_gnome_session\"\n"
"		return\n"
"	elif [ \"X$have_startkde\" != \"X\"    -a \"X$FD_SESS\" = \"Xkde\" ]; then\n"
"		echo \"$have_startkde\"\n"
"		return\n"
"	elif [ \"X$have_twm\" != \"X\"         -a \"X$FD_SESS\" = \"Xtwm\" ]; then\n"
"		echo \"$have_twm\"\n"
"		return\n"
"	elif [ \"X$have_fvwm2\" != \"X\"       -a \"X$FD_SESS\" = \"Xfvwm\" ]; then\n"
"		echo \"$have_fvwm2\"\n"
"		return\n"
"	elif [ \"X$have_xterm\" != \"X\"       -a \"X$FD_SESS\" = \"Xfailsafe\" ]; then\n"
"		echo \"$have_xterm\"\n"
"		return\n"
"	fi\n"
"	home=`csh -f -c \"echo ~$USER\"`\n"
"	if [ \"X$home\" = \"X\" -o ! -d \"$home\" ]; then\n"
"		if [ \"X$have_root\" != \"X\" -a \"X$USER\" != \"Xroot\" ]; then\n"
"			home=`su - $USER -c 'echo $HOME'`\n"
"		fi\n"
"	fi\n"
"	if [ \"X$home\" = \"X\" -o ! -d \"$home\" ]; then\n"
"		if [ -d \"/home/$USER\" ]; then\n"
"			home=\"/home/$USER\"\n"
"		else \n"
"			home=__noplace__\n"
"		fi\n"
"	fi\n"
"	if [ -f \"$home/.dmrc\" ]; then\n"
"		if [ \"X$have_startkde\" != \"X\" ]; then\n"
"			if egrep -i 'Session=(default|kde)' \"$home/.dmrc\" > /dev/null; then\n"
"				echo \"$have_startkde\"\n"
"				return\n"
"			fi\n"
"		fi\n"
"		if [ \"X$have_gnome_session\" != \"X\" ]; then\n"
"			if egrep -i 'Session=gnome' \"$home/.dmrc\" > /dev/null; then\n"
"				echo \"$have_gnome_session\"\n"
"				return\n"
"			fi\n"
"		fi\n"
"		for wm in blackbox fvwm icewm wmw openbox twm windowmaker metacity\n"
"		do\n"
"			eval \"have=\\$have_$wm\"\n"
"			if [ \"X$have\" = \"X\" ]; then\n"
"				continue\n"
"			fi\n"
"			if grep -i \"Session=$wm\" \"$home/.dmrc\" > /dev/null; then\n"
"				echo \"$have\"\n"
"				return\n"
"			fi\n"
"			\n"
"		done\n"
"	fi\n"
"	if [ -f \"$home/.xsession\" ]; then\n"
"		echo \"$home/.xsession\"\n"
"		return\n"
"	elif [ -f \"$home/.xinitrc\" ]; then\n"
"		echo \"$home/.xinitrc\"\n"
"		return\n"
"	fi\n"
"	if [ \"X$have_xterm\" != \"X\" ]; then\n"
"		echo $have_xterm\n"
"		return\n"
"	else\n"
"		echo \".xinitrc\"\n"
"	fi\n"
"}\n"
"\n"
"server() {\n"
"	authfile=`auth`\n"
"	sess=`findsession`\n"
"	DISPLAY=:$N\n"
"	export DISPLAY\n"
"	stmp=\"\"\n"
"	if [ \"X$have_root\" != \"X\" -a \"X$USER\" != \"Xroot\" ]; then\n"
"		sess=\"env DISPLAY=:$N $sess\"\n"
"	fi\n"
"	rmf=\"/nosuch\"\n"
"	if echo \"$sess\" | grep '[ 	]' > /dev/null; then\n"
"		stmp=/tmp/.cd$$`random`\n"
"		rm -f $stmp\n"
"		if [ -f $stmp ]; then\n"
"			exit 1\n"
"		fi\n"
"		touch $stmp\n"
"		chmod 755 $stmp || exit 1\n"
"		echo \"#!/bin/sh\" > $stmp\n"
"		echo \"$sess\"   >> $stmp\n"
"		echo \"sleep 1\"   >> $stmp\n"
"		echo \"rm -f $stmp\" >> $stmp\n"
"		sess=$stmp\n"
"		rmf=\"$stmp\"\n"
"	fi\n"
"	if [ \"X$have_root\" != \"X\" -a \"X$USER\" != \"Xroot\" ]; then\n"
"		ctmp=/tmp/.xat$$`random`\n"
"		rm -f $ctmp\n"
"		if [ -f $ctmp ]; then\n"
"			exit 1\n"
"		fi\n"
"		touch $ctmp\n"
"		chmod 644 $ctmp || exit 1\n"
"		$have_xauth -f $authfile nextract - :$N > $ctmp\n"
"		su - $USER -c \"$have_xauth nmerge - < $ctmp\" 1>&2\n"
"		$have_xauth -f $authfile nextract - `hostname`:$N > $ctmp\n"
"		su - $USER -c \"$have_xauth nmerge - < $ctmp\" 1>&2\n"
"		rm -f $ctmp\n"
"		XAUTHORITY=$authfile\n"
"		export XAUTHORITY\n"
"		sess=\"/bin/su - $USER -c $sess\"\n"
"	else\n"
"		$have_xauth -f $authfile nextract - :$N | $have_xauth nmerge -\n"
"		$have_xauth -f $authfile nextract - `hostname`:$N | $have_xauth nmerge -\n"
"	fi\n"
"\n"
"	result=0\n"
"	ns=4\n"
"	if [ \"X$use_xdmcp_query\" = \"X1\" ]; then\n"
"		# we cannot use -nolisten tcp\n"
"		echo \"$* -once -query localhost\" 1>&2\n"
"		if [ \"X$have_root\" != \"X\" ]; then\n"
"			nohup $* -once -query localhost 1>&2 &\n"
"		else\n"
"			nohup sh -c \"(sleep $ns; $* -once -query localhost -auth $authfile)\" 1>&2 &\n"
"			ns=0\n"
"			result=1\n"
"		fi\n"
"		pid=$!\n"
"	elif [ \"X$have_startx\" != \"X\" -o \"X$have_xinit\" != \"X\" ]; then\n"
"		if [ \"X$have_startx\" != \"X\" ]; then\n"
"			sxcmd=$have_startx\n"
"		else\n"
"			sxcmd=$have_xinit\n"
"		fi\n"
"		echo \"$sxcmd $sess -- $* -nolisten tcp -auth $authfile\" 1>&2\n"
"		if [ \"X$have_root\" != \"X\" ]; then\n"
"			$sxcmd $sess -- $* -nolisten tcp -auth $authfile 1>&2 &\n"
"		else\n"
"			nohup sh -c \"(sleep $ns; $sxcmd $sess -- $* -nolisten tcp -auth $authfile)\" 1>&2 &\n"
"			ns=0\n"
"			result=1\n"
"		fi\n"
"		pid=$!\n"
"	else\n"
"		echo \"$* -nolisten tcp -auth $authfile\" 1>&2\n"
"		if [ \"X$have_root\" != \"X\" ]; then\n"
"			nohup $* -nolisten tcp -auth $authfile 1>&2 &\n"
"			pid=$!\n"
"			sleep 2\n"
"			nohup $sess 1>&2 &\n"
"		else\n"
"			nohup sh -c \"(sleep $ns; $* -nolisten tcp -auth $authfile)\" 1>&2 &\n"
"			pid=$!\n"
"			sleep 2\n"
"			nohup sh -c \"(sleep $ns; $sess)\" 1>&2 &\n"
"			ns=0\n"
"			result=1\n"
"		fi\n"
"	fi\n"
"	sleep $ns\n"
"	if [ \"X$result\" = \"X1\" ]; then\n"
"		:\n"
"	elif [ -d /proc/$pid ]; then\n"
"		result=1\n"
"	elif kill -0 $pid; then\n"
"		result=1\n"
"	else\n"
"		result=0\n"
"	fi\n"
"	if uname | grep SunOS > /dev/null; then\n"
"		nohup sh -c \"(sleep 60; rm -f $rmf)\" 1>&2 &\n"
"	else\n"
"		nohup sh -c \"(sleep 60; rm -f $rmf $authfile)\" 1>&2 &\n"
"	fi\n"
"}\n"
"\n"
"try_X() {\n"
"	if [ \"X$use_xdmcp_query\" = \"X1\" ]; then\n"
"		if [ \"X$have_X\" != \"X\" ]; then\n"
"			server $have_X :$N\n"
"		elif [ \"X$have_Xorg\" != \"X\" ]; then\n"
"			server $have_Xorg :$N\n"
"		elif [ \"X$have_XFree86\" != \"X\" ]; then\n"
"			server $have_XFree86 :$N\n"
"		elif [ \"X$have_Xsun\" != \"X\" ]; then\n"
"			server $have_Xsun :$N\n"
"		fi\n"
"	elif [ \"X$have_xinit\" != \"X\" ]; then\n"
"		save_have_startx=$have_startx\n"
"		have_startx=\"\"\n"
"		server :$N\n"
"		have_startx=$save_have_startx\n"
"	else\n"
"		server :$N\n"
"	fi\n"
"}\n"
"\n"
"try_Xdummy() {\n"
"	if [ \"X$have_Xdummy\" = \"X\" ]; then\n"
"		return\n"
"	fi\n"
"	if [ \"X$have_root\" = \"X\" ]; then\n"
"		return\n"
"	fi\n"
"\n"
"	#save_have_startx=$have_startx\n"
"	#have_startx=\"\"\n"
"	server $have_Xdummy :$N -geom $geom -depth $depth\n"
"	#have_startx=$save_have_startx\n"
"}\n"
"\n"
"try_Xvfb() {\n"
"	if [ \"X$have_Xvfb\" = \"X\" ]; then\n"
"		return\n"
"	fi\n"
"\n"
"	#save_have_startx=$have_startx\n"
"	#have_startx=\"\"\n"
"	sarg=\"-screen\"\n"
"	if uname | grep SunOS > /dev/null; then\n"
"		if grep /usr/openwin/bin/Xsun $have_Xvfb > /dev/null; then\n"
"			sarg=\"screen\"\n"
"			if [ \"X$depth\" = \"X16\" ]; then\n"
"				#depth=24\n"
"				:\n"
"			fi\n"
"		fi\n"
"	fi\n"
"	server $have_Xvfb :$N +kb $sarg 0 ${geom}x${depth}\n"
"	#have_startx=$save_have_startx\n"
"\n"
"	if [ \"X$result\" = \"X1\" -a \"X$have_xmodmap\" != \"X\" ]; then\n"
"		if [ \"X$have_root\" = \"X\" ]; then\n"
"		    nohup sh -c \"(\n"
"			sleep 10;\n"
"			$have_xmodmap -display :$N -e 'keycode any = Shift_R' \\\n"
"				-e 'add Shift = Shift_L Shift_R' \\\n"
"				-e 'keycode any = Control_R' \\\n"
"				-e 'add Control = Control_L Control_R' \\\n"
"				-e 'keycode any = Alt_L' \\\n"
"				-e 'keycode any = Alt_R' \\\n"
"				-e 'keycode any = Meta_L' \\\n"
"				-e 'clear Mod1' \\\n"
"				-e 'add Mod1 = Alt_L Alt_R Meta_L' \\\n"
"		    )\" 1>&2 &\n"
"		else\n"
"		    (\n"
"			sleep 6;\n"
"			$have_xmodmap -display :$N -e 'keycode any = Shift_R' \\\n"
"				-e 'add Shift = Shift_L Shift_R' \\\n"
"				-e 'keycode any = Control_R' \\\n"
"				-e 'add Control = Control_L Control_R' \\\n"
"				-e 'keycode any = Alt_L' \\\n"
"				-e 'keycode any = Alt_R' \\\n"
"				-e 'keycode any = Meta_L' \\\n"
"				-e 'clear Mod1' \\\n"
"				-e 'add Mod1 = Alt_L Alt_R Meta_L' \\\n"
"		    ) 1>&2 &\n"
"		fi\n"
"	fi\n"
"}\n"
"\n"
"cookie() {\n"
"	cookie=\"\"\n"
"	if [ \"X$have_mcookie\" != \"X\" ]; then\n"
"		cookie=`mcookie`\n"
"	elif [ \"X$have_md5sum\" != \"X\" ]; then\n"
"		if [ -c /dev/urandom ]; then\n"
"			cookie=`dd if=/dev/urandom count=32 2>/dev/null | md5sum | awk '{print $1}'`\n"
"		elif [ -c /dev/random ]; then\n"
"			cookie=`dd if=/dev/random count=32 2>/dev/null | md5sum | awk '{print $1}'`\n"
"		fi\n"
"		if [ \"X$cookie\" = \"X\" ]; then\n"
"			r=`random`\n"
"			cookie=`(echo $r; date; uptime; ps -ealf 2>&1) | md5sum | awk '{print $1}'`\n"
"		fi\n"
"	elif [ \"X$have_xauth\" != \"X\" ]; then\n"
"		cookie=`$have_xauth list | awk '{print $NF}' | tail -1`\n"
"	fi\n"
"	if [ \"X$cookie\" = \"X\" ]; then\n"
"		# oh well..\n"
"		for k in 1 2 3 4\n"
"		do\n"
"			r=`random`\n"
"			cookie=$cookie`printf \"%08x\" \"${r}$$\"`\n"
"		done\n"
"	fi\n"
"	echo \"$cookie\"\n"
"}\n"
"\n"
"auth() {\n"
"	if [ \"X$have_xauth\" = \"X\" ]; then\n"
"		exit 1\n"
"	fi\n"
"	tmp=/tmp/.xas$$`random`\n"
"	rm -f $tmp\n"
"	if [ -f $tmp ]; then\n"
"		exit 1\n"
"	fi\n"
"	touch $tmp\n"
"	chmod 600 $tmp || exit 1\n"
"	if [ ! -f $tmp ]; then\n"
"		exit 1\n"
"	fi\n"
"	cook=`cookie`\n"
"	$have_xauth -f $tmp add :$N . $cook  1>&2\n"
"	$have_xauth -f $tmp add `hostname`:$N . $cook  1>&2\n"
"	echo \"$tmp\"\n"
"}\n"
"\n"
"\n"
"depth=${depth:-16}\n"
"geom=${geom:-1280x1024}\n"
"if [ \"X$X11VNC_CREATE_GEOM\" != \"X\" -a \"X$FD_GEOM\" = \"X\" ]; then\n"
"	FD_GEOM=$X11VNC_CREATE_GEOM\n"
"fi\n"
"\n"
"if [ \"X$FD_GEOM\" != \"X\" -a \"X$FD_GEOM\" != \"XNONE\" ]; then\n"
"	x1=`echo \"$FD_GEOM\" | awk -Fx '{print $1}'`\n"
"	y1=`echo \"$FD_GEOM\" | awk -Fx '{print $2}'`\n"
"	d1=`echo \"$FD_GEOM\" | awk -Fx '{print $3}'`\n"
"	if [ \"X$x1\" != \"X\" -a \"X$y1\" != \"X\" ]; then\n"
"		geom=\"${x1}x${y1}\"\n"
"	fi\n"
"	if [ \"X$d1\" != \"X\" ]; then\n"
"		depth=\"${d1}\"\n"
"	fi\n"
"fi\n"
"\n"
"if [ \"X$USER\" = \"X\" ]; then\n"
"	USER=$LOGNAME\n"
"fi\n"
"if [ \"X$USER\" = \"X\" ]; then\n"
"	USER=`whoami`\n"
"fi\n"
"\n"
"PATH=$PATH:/usr/X11R6/bin:/usr/bin/X11:/usr/openwin/bin:/usr/dt/bin:/opt/kde3/bin:/opt/gnome/bin:/usr/bin:/bin:/usr/sfw/bin\n"
"\n"
"have_root=\"\"\n"
"id0=`id`\n"
"if id | grep -w root > /dev/null; then\n"
"	have_root=\"1\"\n"
"fi\n"
"\n"
"p_ok=0\n"
"if [ \"`type -p /bin/sh`\" = \"/bin/sh\" ]; then\n"
"	p_ok=1\n"
"fi\n"
"\n"
"for prog in startx xinit xdm gdm kdm xterm Xdummy Xvfb xauth mcookie md5sum xmodmap startkde gnome-session blackbox fvwm2 mwm openbox twm windowmaker metacity X Xorg XFree86 Xsun Xsession netstat\n"
"do\n"
"	p2=`echo \"$prog\" | sed -e 's/-/_/g'`\n"
"	eval \"have_$p2=''\"\n"
"	if type $prog > /dev/null 2>&1; then\n"
"		bpath=`which $prog | awk '{print $NF}'`\n"
"		if [ ! -x \"$bpath\" -o -d \"$bpath\" ]; then\n"
"			if [ \"X$p_ok\" = \"X1\" ]; then\n"
"				bpath=`type -p $prog | awk '{print $NF}'`\n"
"			fi\n"
"			if [ ! -x \"$bpath\" -o -d \"$bpath\" ]; then\n"
"				bpath=`type $prog | awk '{print $NF}'`\n"
"			fi\n"
"		fi\n"
"		eval \"have_$p2=$bpath\"\n"
"	fi\n"
"done\n"
"\n"
"N=`findfree`\n"
"\n"
"if [ \"X$N\" = \"X\" ]; then\n"
"	exit 1\n"
"fi\n"
"echo \"trying N=$N ...\" 1>&2\n"
"\n"
"if [ \"X$CREATE_DISPLAY_OUTPUT\" != \"X\" ]; then\n"
"	set | grep \"^have_\" 1>&2\n"
"fi\n"
"\n"
"TRY=\"$1\"\n"
"if [ \"X$TRY\" = \"X\" ]; then\n"
"	TRY=Xdummy,Xvfb\n"
"fi\n"
"\n"
"for curr_try in `echo \"$TRY\" | tr ',' ' '`\n"
"do\n"
"	result=0\n"
"	use_xdmcp_query=0\n"
"	if echo \"$curr_try\" | egrep '[+.-]xdmcp' > /dev/null; then\n"
"		use_xdmcp_query=1\n"
"	fi\n"
"	curr_try=`echo \"$curr_try\" | sed -e  's/[+.-]xdmcp//'`\n"
"	\n"
"	if echo \"$curr_try\" | grep -iw \"Xdummy\" > /dev/null; then\n"
"		try_Xdummy\n"
"	elif echo \"$curr_try\" | grep -iw \"Xvfb\" > /dev/null; then\n"
"		try_Xvfb\n"
"	elif echo \"$curr_try\" | grep -iw \"X\" > /dev/null; then\n"
"		try_X\n"
"	fi\n"
"	if [ \"X$result\" = \"X1\" ]; then\n"
"		echo \"DISPLAY=:$N\"\n"
"		$have_xauth -f $authfile extract - :$N\n"
"		exit 0\n"
"	fi\n"
"done\n"
"\n"
"exit 1\n"
;

#endif /* _SSLTOOLS_H */