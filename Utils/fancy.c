/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fancy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labintei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 18:00:15 by labintei          #+#    #+#             */
/*   Updated: 2021/09/27 20:16:16 by labintei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ascii_art(void)
{
	printf("\033[1;32m\n");
	printf("___  ____       _     _          _ _ \n");
	printf("|  \\/  (_)     (_)   | |        | | |\n");
	printf("| .  . |_ _ __  _ ___| |__   ___| | |\n");
	printf("| |\\/| | | '_ \\| / __| '_ \\ / _ \\ | |\n");
	printf("| |  | | | | | | \\__ \\ | | |  __/ | |\n");
	printf("\\_|  |_/_|_| |_|_|___/_| |_|\\___|_|_|\n");
	printf("\033[0m\n\n\n");
}
