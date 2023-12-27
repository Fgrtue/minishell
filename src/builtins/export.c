/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkopnev <kkopnev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/23 14:37:22 by kkopnev       #+#    #+#                 */
/*   Updated: 2023/12/23 16:48:39 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*

EXPORT

    WITHOUT ARGUMENTS

        Output: key="vale" pairs (NOTE: dquotes!). If the value was exported
        in the single quotes, then any metacaracter is preceeded with the '\'
        sign. If it was exported in double quotes, then everuthing is expanded.

        IN FACT we could output just env in alphabetical order. 

    WITH ARGUMENTS

        0. Search for all the arguments that are of the shape key=value.
        value can be:
            a. word
            b. env variable
            c. string in double quotes
            d. string in single quotes
        key can be:
            a. word
            b. env variable (only one!)
        i.e. key cannot be something that consists of several
        elements (either separated with the space or in the quotes
        with spaces)
        1. If the value is in dquotes -- expand env variables and unite
        all of the elements in the quotes
        2. If the value is in single quotes -- don't expand the env variables
        and unite everything together
        3. If the value is an env variable -- expand it
        4, If it is a word -- leave it like that
        5. Once you obtained a string, just add key=value (expanded key and value)
        to the environment in the bottom

*/