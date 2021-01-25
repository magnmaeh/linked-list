/*
 * Copyright (C) 2020 Magnus Mæhlum
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef DEBUG_H
#define DEBUG_H

#define DO_DEBUG

#if defined(DO_DEBUG)
    #define DEBUG(str) str
#else
    #define DEBUG(str)
#endif

#if defined(DO_DEBUG)
    #include <stdio.h>
    #define print_error(format, ...) printf("Error in %s(): ", __func__); printf(format, ##__VA_ARGS__);
#endif


#define PRINT_LINE printf("Line: %d\n", __LINE__);

#endif // DEBUG_H