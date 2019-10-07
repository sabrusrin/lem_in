# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    nodes.py                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adavis <adavis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/18 17:04:31 by adavis            #+#    #+#              #
#    Updated: 2019/09/18 19:24:14 by adavis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from dataclasses import dataclass

@dataclass
class	Node:
	name: str
	x: int
	y: int
	start: bool
	end: bool

	def __repr__(self):
		return ' '.join([self.name, str(self.x), str(self.y)])

