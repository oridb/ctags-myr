
/*
*   Copyright (c) 2014, Ori Bernstein
*
*   This source code is released for free distribution under the terms of the
*   GNU General Public License.
*
*   This module contains functions for generating tags for Myrddin language
*   files.
*/
/*
*   INCLUDE FILES
*/
#include "general.h"  /* must always come first */

#include <string.h>

#include "parse.h"

/*
*   DATA DEFINITIONS
*/
static kindOption PythonKinds[] = {
    {TRUE, 'f', "function",     "functions"},
    {TRUE, 'v', "variable",     "variables"},
    {TRUE, 'n', "namespace",    "namespace"},
};


static void installMyrddinRegex (const langType language)
{
	addTagRegex (language,
		"^(\\s*extern)?\\s*const\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=.*$",
		"\\2", "f,function,functions", NULL);
	addTagRegex (language,
		"^(\\s*extern)?\\s*var\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=.*$",
		"\\2", "v,var,variables", NULL);
	addTagRegex (language,
		"^\\s*pkg\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=$",
		"\\1", "p,pkg,packages", NULL);
}


parserDefinition *MyrddinParser (void)
{
    static const char *const extensions[] = { "myr", NULL };
    parserDefinition *def = parserNew ("Myrddin");
    def->extensions = extensions;
    def->initialize = installMyrddinRegex;
    def->regex      = TRUE;
    return def;
}
