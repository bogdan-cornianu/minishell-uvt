#include <argp.h>
#include <errno.h>
#include <stdio.h>

#include <misc.h>
#include <libpasswd.h>

#define PRG_NAME passwd;	/** Name shown by --help etc */

extern const char *progname;	/** Used to store the name of the program */

/** Address to send bug-reports to */
const char *argp_program_bug_address = PACKAGE_BUGREPORT;

/** Usage information */
static char args_doc[] =
	N_(&quot;[USER]\n&quot;
	   &quot;-s&quot;);

/** Program synopsis */
static char doc[] =
	N_(&quot;Change the password of the specified user.\n&quot;
	   &quot;\n&quot;
	   &quot;If no name is specified, &quot;
	   &quot;the password of the current user is changed.&quot;);

/** Arguments available in passwd */
struct passwd_options_t
{
	struct setpasswd_options_t setpasswd;
	const char *name;
	int update_if_expired;
};

/**
 * Parse a single option
 *
 * @param key The option
 * @param arg The argument for the option
 * @param state The state of argp
 * @return 0 on success,
 *         ARGP_ERR_UNKNOWN on failure
 */
static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
  	struct passwd_options_t *args = state-&gt;input;
	arg = NULL;

	switch (key) {
	case 'u':
	case 'k':
	  	args-&gt;update_if_expired = 1;
	  	break;

	case ARGP_KEY_INIT:
		args-&gt;name = NULL;
		state-&gt;child_inputs[0] = &amp;args-&gt;setpasswd;
		break;

	case ARGP_KEY_ARG:
		if (args-&gt;name)
			argp_usage(state);

		args-&gt;name = arg;
		break;

	default:
		return ARGP_ERR_UNKNOWN;
	}

	return 0;
}

/**
 * The program's main-function
 *
 * @param argc The number of arguments
 * @param argv The arguments
 * @return 0 on success, errno on failure
 */
int main(int argc, char *argv[])
{
	error_t status = 0;

	/* argp parser */
	static const struct argp_child child_parsers[] = {
		{ &amp;setpasswd_argp, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	};

	/** Structure with the available command line options */
	static struct argp_option options[] = {
		{ &quot;update-if-expired&quot;, 'u', 0, 0,
	  	N_(&quot;Only update password if it has expired&quot;), 0 },
		{ &quot;keep-tokens&quot;, 'k', 0, OPTION_HIDDEN,
	  	N_(&quot;Only update password if it has expired&quot;), 0 },
		{ 0, 0, 0, 0, 0, 0 }
	};

	struct argp argp = {
		.options	= options,
		.parser		= parse_opt,
		.args_doc	= args_doc,
		.doc		= doc,
		.children	= child_parsers,
	};

	struct passwd_options_t args;

	argp_program_version_hook = version;

	errno = 0;

	/* Initialise support for locales, and set the program-name */
	if ((status = init_locales(PRG_NAME)))
		return status;

	

	/* Parse command line */
	if ((status = argp_parse(&amp;argp, argc, argv, 0, 0, &amp;args))) {
		if (status != EINVAL)
			fprintf(stderr,
				_(&quot;%s: `%s' failed; %s\n&quot;),
				progname, &quot;argp_parse()&quot;, strerror(status));

		return status;
	}

	return setpasswd(args.name, 0, args.setpasswd.removepass, 
			 args.setpasswd.showhash, args.update_if_expired);
