// ----------------------------------------------------------------------------
// Copyright 2016-2019 ARM Ltd.
//
// SPDX-License-Identifier: Apache-2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------------------------------------------------------

#ifndef SCREEN_CONSOLE_API_H
#define SCREEN_CONSOLE_API_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void screen_console_init(void);
void screen_console_clear_line(size_t line);
void screen_console_write_line(size_t line, const char* string);

#ifdef __cplusplus
}
#endif

#endif
