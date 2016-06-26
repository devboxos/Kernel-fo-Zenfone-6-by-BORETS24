/*
 * Support for Intel Camera Imaging ISP subsystem.
 *
 * Copyright (c) 2010 - 2014 Intel Corporation. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */

#define IA_CSS_INCLUDE_STATES
#include "ia_css_memory_access.h"
#include "isp/kernels/cnr/cnr_1.0/ia_css_cnr.host.h"
#include "isp/kernels/cnr/cnr_2/ia_css_cnr2.host.h"
#include "isp/kernels/de/de_1.0/ia_css_de.host.h"
#include "isp/kernels/dp/dp_1.0/ia_css_dp.host.h"
#include "isp/kernels/ref/ref_1.0/ia_css_ref.host.h"
#include "isp/kernels/tnr/tnr_1.0/ia_css_tnr.host.h"
#include "isp/kernels/ynr/ynr_1.0/ia_css_ynr.host.h"
/* Generated code: do not edit or commmit. */

#ifndef _IA_CSS_ISP_STATE_H
#define _IA_CSS_ISP_STATE_H

/* Code generated by genparam/gencode.c:gen_param_enum() */

enum ia_css_state_ids {
	IA_CSS_CNR_STATE_ID,
	IA_CSS_CNR2_STATE_ID,
	IA_CSS_DP_STATE_ID,
	IA_CSS_DE_STATE_ID,
	IA_CSS_TNR_STATE_ID,
	IA_CSS_REF_STATE_ID,
	IA_CSS_YNR_STATE_ID,
	IA_CSS_NUM_STATE_IDS
};

/* Code generated by genparam/gencode.c:gen_param_offsets() */

struct ia_css_state_memory_offsets {
	struct {
		struct ia_css_isp_parameter cnr;
		struct ia_css_isp_parameter cnr2;
		struct ia_css_isp_parameter dp;
		struct ia_css_isp_parameter de;
		struct ia_css_isp_parameter ynr;
	} vmem;
	struct {
		struct ia_css_isp_parameter tnr;
		struct ia_css_isp_parameter ref;
	} dmem;
};

#if defined(IA_CSS_INCLUDE_STATES)

#include "ia_css_stream.h"   /* struct ia_css_stream */
#include "ia_css_binary.h"   /* struct ia_css_binary */
/* Code generated by genparam/genstate.c:gen_state_init_table() */

extern void (* ia_css_kernel_init_state[IA_CSS_NUM_STATE_IDS])(const struct ia_css_binary *binary);

#endif /* IA_CSS_INCLUDE_STATE */

#endif /* _IA_CSS_ISP_STATE_H */