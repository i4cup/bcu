/*
* Copyright 2020-2021 NXP.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* Redistributions of source code must retain the above copyright notice, this
* list of conditions and the following disclaimer.
*
* Redistributions in binary form must reproduce the above copyright notice, this
* list of conditions and the following disclaimer in the documentation and/or
* other materials provided with the distribution.
*
* Neither the name of the NXP Semiconductor nor the names of its
* contributors may be used to endorse or promote products derived from this
* software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*/
#ifndef BCU_YAML_H
#define BCU_YAML_H

#include <stdio.h>

#ifdef _WIN32
#include "libyaml/include/yaml.h"
#endif
#if defined(linux) || defined(__APPLE__)
#include <yaml.h>
#endif
#include "board.h"
#include "bcu_parser.h"
#include "version.h"

enum yaml_now_status_type {
	STATUS_CHECK_VERSION,
	STATUS_WAITING_WANTED_BOARD,
	STATUS_CHANGE_BOARD,
	STATUS_CHANGE_FIXEDRAIL,
	STATUS_CHANGE_RAIL,
	STATUS_CHANGE_RSENSE1,
	STATUS_CHANGE_RSENSE2,
	STATUS_CHANGE_SHOWID,
	STATUS_CHANGE_DEFAULT_RS,
	STATUS_GROUPS,
	STATUS_CHANGE_GROUPS
};

struct bcu_yaml_version
{
	char* version;
};

/*
 * The caller owns the file handle and should open it in write mode with the
 * stream positioned at the beginning of the target config file.
 */
int writeConf(FILE* fp);

/*
 * The caller owns the file handle and should open it in read mode.
 * config_path should point to the same config file and is used for diagnostics
 * and automatic in-place config-version updates when needed.
 */
int readConf(FILE* fh, const char* config_path, const char* boardname, struct options_setting* setting);

#endif //BCU_YAML_H
