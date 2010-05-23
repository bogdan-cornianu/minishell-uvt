#include <lvsmon.h>
#include <banner.h>
#include <util.h>
#include <ctype.h>
#include <string.h>

static const char rcsid[]=
	"@(#) $Id: banner.c,v 1.4 2002/05/15 08:52:46 gianni Exp $";

plugin_t banner_plugin={
	NULL, 
	"banner",
	NULL, 
	banner_check,
	banner_validate, 
	banner_errno,
	1024
};

int banner_errno(char *buf, int buflen, int err)
{
	switch (err) {
		case BANNER_ERR_TOO_SMALL:
			return snprintf(buf, buflen,
				"Search string is bigger than banner");
		case BANNER_ERR_NOT_FOUND:
			return snprintf(buf, buflen,
				"Search string not found");
	}
	return 0;
}

int banner_validate(char *conf, void **priv)
{
	p_banner_priv p;

	if ( !(p=malloc(sizeof(banner_priv_t))) ) return 0;
	if ( !(p->banner=strdup(conf)) ) {
		free(p);
		return 0;
	}

	p->len=strlen(p->banner);
	*priv=p;
	return 1;
}

int banner_check(char *buf, int len, void *priv, int *errnum)
{
	p_banner_priv p=(p_banner_priv)priv;
	u_int32_t i;
	char *str;

	/* Don't check */
	if ( !p->len ) return 1;

	/* If substring cant't fit, then its an obvious fail */
	if ( len < p->len ) {
		*errnum=BANNER_ERR_TOO_SMALL;
		return 0;
	}

	/* memcmp() is safe with binary data */
	for(str=buf, i=0; i<len-p->len; i++, str++){
		if ( memcmp(p->banner, str, p->len)==0 ) return 1;
	}

	*errnum=BANNER_ERR_NOT_FOUND;
	
	return 0;
}

