/*
 * Copyright 2012 Red Hat Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ben Skeggs
 */

#include <engine/software.h>
#include <engine/disp.h>

#include <core/class.h>

#include "nv50.h"

static struct nouveau_oclass
nv84_disp_sclass[] = {
	{ NV84_DISP_MAST_CLASS, &nv50_disp_mast_ofuncs },
	{ NV84_DISP_SYNC_CLASS, &nv50_disp_sync_ofuncs },
	{ NV84_DISP_OVLY_CLASS, &nv50_disp_ovly_ofuncs },
	{ NV84_DISP_OIMM_CLASS, &nv50_disp_oimm_ofuncs },
	{ NV84_DISP_CURS_CLASS, &nv50_disp_curs_ofuncs },
	{}
};

struct nouveau_omthds
nv84_disp_base_omthds[] = {
	{ SOR_MTHD(NV50_DISP_SOR_PWR)         , nv50_sor_mthd },
	{ SOR_MTHD(NV84_DISP_SOR_HDMI_PWR)    , nv50_sor_mthd },
	{ SOR_MTHD(NV50_DISP_SOR_LVDS_SCRIPT) , nv50_sor_mthd },
	{ DAC_MTHD(NV50_DISP_DAC_PWR)         , nv50_dac_mthd },
	{ DAC_MTHD(NV50_DISP_DAC_LOAD)        , nv50_dac_mthd },
	{ PIOR_MTHD(NV50_DISP_PIOR_PWR)       , nv50_pior_mthd },
	{ PIOR_MTHD(NV50_DISP_PIOR_TMDS_PWR)  , nv50_pior_mthd },
	{ PIOR_MTHD(NV50_DISP_PIOR_DP_PWR)    , nv50_pior_mthd },
	{},
};

static struct nouveau_oclass
nv84_disp_base_oclass[] = {
	{ NV84_DISP_CLASS, &nv50_disp_base_ofuncs, nv84_disp_base_omthds },
	{}
};

static int
nv84_disp_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	       struct nouveau_oclass *oclass, void *data, u32 size,
	       struct nouveau_object **pobject)
{
	struct nv50_disp_priv *priv;
	int ret;

	ret = nouveau_disp_create(parent, engine, oclass, 2, "PDISP",
				  "display", &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nv_engine(priv)->sclass = nv84_disp_base_oclass;
	nv_engine(priv)->cclass = &nv50_disp_cclass;
	nv_subdev(priv)->intr = nv50_disp_intr;
	INIT_WORK(&priv->supervisor, nv50_disp_intr_supervisor);
	priv->sclass = nv84_disp_sclass;
	priv->head.nr = 2;
	priv->dac.nr = 3;
	priv->sor.nr = 2;
	priv->pior.nr = 3;
	priv->dac.power = nv50_dac_power;
	priv->dac.sense = nv50_dac_sense;
	priv->sor.power = nv50_sor_power;
	priv->sor.hdmi = nv84_hdmi_ctrl;
	priv->pior.power = nv50_pior_power;
	priv->pior.dp = &nv50_pior_dp_func;
	return 0;
}

struct nouveau_oclass
nv84_disp_oclass = {
	.handle = NV_ENGINE(DISP, 0x82),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv84_disp_ctor,
		.dtor = _nouveau_disp_dtor,
		.init = _nouveau_disp_init,
		.fini = _nouveau_disp_fini,
	},
};
