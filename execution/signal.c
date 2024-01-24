/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:49:27 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/21 17:37:53 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"


#define UNUSED(x) (void)(x)

void sigint_handler(int signo) {
    UNUSED(signo);
    printf("\nMINISHELL$ ");
    fflush(stdout);
}

void sigquit_handler(int signo) {
    UNUSED(signo);
}

void sigterm_handler(int signo) {
    UNUSED(signo);
    printf("\nExiting MINISHELL...\n");
    exit(0);
}

void set_signals() {
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("Error setting up SIGINT handler");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGQUIT, sigquit_handler) == SIG_ERR) {
        perror("Error setting up SIGQUIT handler");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGTERM, sigterm_handler) == SIG_ERR) {
        perror("Error setting up SIGTERM handler");
        exit(EXIT_FAILURE);
    }
}
