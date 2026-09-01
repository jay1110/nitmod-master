console2-16bit
{
	nopicmip
	{
		map ui/assets/et_logo.tga
		blendFunc add	
	}
}

models/players/common/specGlow
{
	cull none
	{
		map $whiteimage
		blendFunc gl_one gl_one
		rgbGen entity
	}
}


images/blackmask
{
	nopicmip 
	nocompress
	nomipmaps
	{
		map gfx/2d/mapmask.tga
		depthwrite
		blendfunc blend
		rgbGen identity
		alphaGen vertex
	}
}

sprites/voicemedic_cm
{
	nopicmip
	nocompress
	nomipmaps
	{
		map sprites/voicemedic.tga
		depthFunc equal
		blendfunc blend
		rgbGen vertex
		alphaGen vertex
	}
}

sprites/objective_cm
{
	nopicmip
	nocompress
	nomipmaps
	{
		map sprites/objective.tga
		depthFunc equal
		blendfunc blend
		rgbGen vertex
		alphaGen vertex
	}
}

icons/iconw_landmine_1_select
{
	nomipmaps
	nopicmip
	{
		map icons/iconw_landmine_1_select.tga
		blendFunc blend
		rgbGen vertex
	}
}

icons/iconw_m1_garand_1_select
{
	nomipmaps
	nopicmip
	{
		map icons/iconw_m1_garand_1_select.tga
		blendFunc blend
		rgbGen vertex
	}
}

icons/iconw_m1_garand_gren_1_select
{
	nomipmaps
	nopicmip
	{
		map icons/iconw_m1_garand_gren_1_select.tga
		blendFunc blend
		rgbGen vertex
	}
}

icons/iconw_kar98_1_select
{
	nomipmaps
	nopicmip
	{
		map icons/iconw_kar98_1_select.tga
		blendFunc blend
		rgbGen vertex
	}
}

icons/iconw_kar98_gren_1_select
{
	nomipmaps
	nopicmip
	{
		map icons/iconw_kar98_gren_1_select.tga
		blendFunc blend
		rgbGen vertex
	}
}

icons/iconw_fg42_1_select
{
	nomipmaps
	nopicmip
	{
		map icons/iconw_fg42_1_select.tga
		blendFunc blend
		rgbGen vertex
	}
}

icons/iconw_mg42_1_select
{
	nomipmaps
	nopicmip
	{
		map icons/iconw_mg42_1_select.tga
		blendFunc blend
		rgbGen vertex
	}
}

icons/iconw_mortar_1_select
{
	nomipmaps
	nopicmip
	{
		map icons/iconw_mortar_1_select.tga
		blendFunc blend
		rgbGen vertex
	}
}

icons/iconw_syringe_1_select
{
	nomipmaps
	nopicmip
	{
		map icons/iconw_syringe_1_select.tga
		blendFunc blend
		rgbGen vertex
	}
}

icons/iconw_syringe2_1_select
{
	nomipmaps
	nopicmip
	{
		map icons/iconw_syringe2_1_select.tga
		blendFunc blend
		rgbGen vertex
	}
}

icons/iconw_binoculars_1_select
{
	nomipmaps
	nopicmip
	{
		map icons/iconw_binoculars_1_select.tga
		blendFunc blend
		rgbGen vertex
	}
}

icons/iconw_satchel_1_select
{
	nomipmaps
	nopicmip
	{
		map icons/iconw_satchel_1_select.tga
		blendFunc blend
		rgbGen vertex
	}
}

icons/iconw_radio_1_select
{
	nomipmaps
	nopicmip
	{
		map icons/iconw_radio_1_select.tga
		blendFunc blend
		rgbGen vertex
	}
}

icons/iconw_silencer_1_select
{
	nomipmaps
	nopicmip
	{
		map icons/iconw_silencer_1_select.tga
		blendFunc blend
		rgbGen vertex
	}
}

gfx/2d/net
{
        nocompress
        nopicmip
        {
                map gfx/2d/net.jpg
                blendfunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
        }
}

nitmod/mp5
{
	{
		map textures/effects/envmap_slate.tga
		rgbGen lightingdiffuse
		tcGen environment
	}
	{
		map models/weapons2/mp5/mp5.tga
		blendFunc GL_ONE GL_ONE_MINUS_SRC_ALPHA
		rgbGen lightingdiffuse
	}
}

shaderfix/rank1 
{ 
	{
	 map models/players/temperate/common/rank1.tga
	 alphaFunc GE128 rgbGen lightingDiffuse 
	 }
}

shaderfix/rank2
{ 
	{
	 map models/players/temperate/common/rank2.tga
	 alphaFunc GE128 rgbGen lightingDiffuse 
	 }
}

shaderfix/rank3 
{ 
	{
	 map models/players/temperate/common/rank3.tga
	 alphaFunc GE128 rgbGen lightingDiffuse 
	 }
}

shaderfix/rank4
{ 
	{
	 map models/players/temperate/common/rank4.tga
	 alphaFunc GE128 rgbGen lightingDiffuse 
	 }
}

shaderfix/rank5
{ 
	{
	 map models/players/temperate/common/rank5.tga
	 alphaFunc GE128 rgbGen lightingDiffuse 
	 }
}

shaderfix/rank6
{ 
	{
	 map models/players/temperate/common/rank6.tga
	 alphaFunc GE128 rgbGen lightingDiffuse 
	 }
}

shaderfix/rank7
{ 
	{
	 map models/players/temperate/common/rank7.tga
	 alphaFunc GE128 rgbGen lightingDiffuse 
	 }
}

shaderfix/rank8
{ 
	{
	 map models/players/temperate/common/rank8.tga
	 alphaFunc GE128 rgbGen lightingDiffuse 
	 }
}

shaderfix/rank9
{ 
	{
	 map models/players/temperate/common/rank9.tga
	 alphaFunc GE128 rgbGen lightingDiffuse 
	 }
}

shaderfix/rank10
{ 
	{
	 map models/players/temperate/common/rank10.tga
	 alphaFunc GE128 rgbGen lightingDiffuse 
	 }
}

shaderfix/rank11 
{ 
	{
	 map models/players/temperate/common/rank11.tga
	 alphaFunc GE128 rgbGen lightingDiffuse 
	 }
}

//N!trox* - From ETPub:
// forty - transparent gun models
textures/sfx/transgunRed
{ 
     noPicmip 
     surfaceparm trans 
     { 
          map textures/sfx/construction.tga
          blendFunc GL_SRC_ALPHA GL_ONE
          rgbgen const ( 0.5 0.10 0.10 )
          tcMod scroll 0.025 0.025 
     } 
}

textures/sfx/transgunGreen
{ 
     noPicmip 
     surfaceparm trans 
     { 
          map textures/sfx/construction.tga
          blendFunc GL_SRC_ALPHA GL_ONE
          rgbgen const ( 0.10 0.5 0.10 )
          tcMod scroll 0.025 0.025 
     } 
}

textures/sfx/transgunBlue
{ 
     noPicmip 
     surfaceparm trans 
     { 
          map textures/sfx/construction.tga
          blendFunc GL_SRC_ALPHA GL_ONE
          rgbgen const ( 0.10 0.10 0.5 )
          tcMod scroll 0.025 0.025 
     } 
}

textures/sfx/transgunWhite
{ 
     noPicmip 
     surfaceparm trans 
     { 
          map textures/sfx/construction.tga
          blendFunc GL_SRC_ALPHA GL_ONE
          rgbgen const ( 0.35 0.35 0.35 )
          tcMod scroll 0.025 0.025 
     } 
}

nitmod/SpecMines
{
	cull none
	deformVertexes wave 1 sin -0.5 0 0 1
	noPicmip
	surfaceparm trans
	{
		map textures/sfx/construction.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen entity
		tcGen environment
		tcMod scroll 0.025 -0.07625
	}
}

icons/iconw_mp5_1_select
{
	nomipmaps
	nopicmip
	{
		map icons/iconw_mp5_1_select.tga
		blendFunc blend
		rgbGen vertex
	}
}

textures/egypt_floor_sd/marblefloor_c04
{
	{
		map textures/goldrush-env.tga
		rgbGen identity
		tcGen environment
		tcMod scale 0.9 0.9
	}
	{
		map textures/egypt_floor_sd/marblefloor_c04.tga
		blendfunc blend
		rgbGen identity
	}
	{
		map $lightmap
		blendfunc filter
		rgbGen identity
	}
}

models/multiplayer/syringe/poison
{
	cull disable
	{
		map gfx/misc/poisonfluid.tga
		rgbGen lightingDiffuse
		tcMod scale 2 2
		tcMod scroll 0 -0.2
		tcMod turb 0 0.4 0 0.1
	}
	{
		map gfx/misc/poisonfluid.tga
		blendfunc blend
		rgbGen lightingDiffuse
		tcMod scale 2 1.7
		tcMod scroll 0 -0.21
		tcMod turb 0 0.1 0 0.1
	}
	{
		map gfx/misc/poisonfluid.tga
		blendfunc blend
		rgbGen lightingDiffuse
		tcMod scale 1.5 2.5
		tcMod scroll 0 -0.21
		tcMod turb 0 0.35 0 0.1
	}
	{
		map models/multiplayer/syringe/syringePoison.tga
		blendfunc blend
		rgbGen lightingDiffuse
	}
	{
		map models/multiplayer/syringe/syringe_reflections.tga
		blendfunc blend
		rgbGen lightingDiffuse
	}
}

sprites/poisoned
{
	nocompress
	nopicmip
	{
		map sprites/poisoned.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/limbo/cm_dynamite
{
	nopicmip
	nocompress
	nomipmaps
	{
		map gfx/limbo/cm_dynamite.tga
		depthFunc equal
		blendfunc blend
		rgbGen vertex
		alphaGen vertex
	}
}

gfx/limbo/dynamite
{
	nopicmip
	nocompress
	nomipmaps
	{
		map gfx/limbo/cm_dynamite.tga
		blendfunc blend
		rgbGen vertex
		alphaGen vertex
	}
}

gfx/limbo/bflag
{
	nopicmip
	nocompress
	nomipmaps
	{
		map gfx/limbo/cm_flagallied.tga
		blendfunc blend
		rgbGen vertex
		alphaGen vertex
	}
}

gfx/limbo/rflag
{
	nopicmip
	nocompress
	nomipmaps
	{
		map gfx/limbo/cm_flagaxis.tga
		blendfunc blend
		rgbGen vertex
		alphaGen vertex
	}
}

gfx/limbo/cm_flagallied
{
	nopicmip
	nocompress
	nomipmaps
	{
		map gfx/limbo/cm_flagallied.tga
		depthFunc equal
		blendfunc blend
		rgbGen vertex
		alphaGen vertex
	}
}

gfx/limbo/cm_flagaxis
{
	nopicmip
	nocompress
	nomipmaps
	{
		map gfx/limbo/cm_flagaxis.tga
		depthFunc equal
		blendfunc blend
		rgbGen vertex
		alphaGen vertex
	}
}

icons/iconw_tripmine_1_select
{
	nomipmaps
	nopicmip
	{
		map icons/iconw_tripmine_1_select.tga
		blendFunc blend
		rgbGen vertex
	}
}

models/multiplayer/landmine/plandmine
{
	{
		map textures/effects/envmap_slate_90.tga
		rgbGen lightingdiffuse
		tcGen environment
	}
	{
		map models/multiplayer/landmine/landmine2.jpg
		blendFunc GL_ONE GL_ONE_MINUS_SRC_ALPHA
		rgbGen lightingdiffuse
	}
}

icons/iconw_plandmine_1_select
{
	nomipmaps
	nopicmip
	{
		map icons/iconw_plandmine_1_select.tga
		blendFunc blend
		rgbGen vertex
	}
}

models/multiplayer/mine_marker/allied_marker2
{
	cull disable
	nomipmaps
	nopicmip
	{
		map models/multiplayer/mine_marker/allied_marker2.tga
		rgbGen lightingdiffuse
	}
}

models/multiplayer/mine_marker/axis_marker2
{
	cull disable
	nomipmaps
	nopicmip
	{
		map models/multiplayer/mine_marker/axis_marker2.tga
		rgbGen lightingdiffuse
	}
}

//ETPro crosshairs
gfx/2d/crosshairk
{
	nocompress
	nopicmip
	{
		map gfx/2d/crosshairk.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/2d/crosshairk_alt
{
	nocompress
	nopicmip
	{
		map gfx/2d/crosshaira_alt.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/2d/crosshairl
{
	nocompress
	nopicmip
	{
		map gfx/2d/crosshairl.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/2d/crosshairl_alt
{
	nocompress
	nopicmip
	{
		map gfx/2d/crosshairl_alt.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/2d/crosshairm
{
	nocompress
	nopicmip
	{
		map gfx/2d/crosshairc.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/2d/crosshairm_alt
{
	nocompress
	nopicmip
	{
		map gfx/2d/crosshairp.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/2d/crosshairn
{
	nocompress
	nopicmip
	{
		map gfx/2d/crosshaird.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/2d/crosshairn_alt
{
	nocompress
	nopicmip
	{
		map gfx/2d/crosshairp.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/2d/crosshairo
{
	nocompress
	nopicmip
	{
		map gfx/2d/crosshaire.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/2d/crosshairo_alt
{
	nocompress
	nopicmip
	{
		map gfx/2d/crosshairp.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/2d/crosshairp
{
	nocompress
	nopicmip
	{
		map gfx/2d/crosshairp.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/2d/crosshairp_alt
{
	nocompress
	nopicmip
	{
		map gfx/2d/crosshairf_alt.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/awards/0
{
	nocompress
	nopicmip
	{
		map gfx/awards/0.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/awards/1
{
	nocompress
	nopicmip
	{
		map gfx/awards/1.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/awards/2
{
	nocompress
	nopicmip
	{
		map gfx/awards/2.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/awards/3
{
	nocompress
	nopicmip
	{
		map gfx/awards/3.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/awards/4
{
	nocompress
	nopicmip
	{
		map gfx/awards/4.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/awards/5
{
	nocompress
	nopicmip
	{
		map gfx/awards/5.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/awards/6
{
	nocompress
	nopicmip
	{
		map gfx/awards/6.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/awards/7
{
	nocompress
	nopicmip
	{
		map gfx/awards/7.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/awards/8
{
	nocompress
	nopicmip
	{
		map gfx/awards/8.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/awards/9
{
	nocompress
	nopicmip
	{
		map gfx/awards/9.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/awards/10
{
	nocompress
	nopicmip
	{
		map gfx/awards/10.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/awards/11
{
	nocompress
	nopicmip
	{
		map gfx/awards/11.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/awards/12
{
	nocompress
	nopicmip
	{
		map gfx/awards/12.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/awards/13
{
	nocompress
	nopicmip
	{
		map gfx/awards/13.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/awards/14
{
	nocompress
	nopicmip
	{
		map gfx/awards/14.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/awards/15
{
	nocompress
	nopicmip
	{
		map gfx/awards/15.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/2d/objArrow
{
	nocompress
	nopicmip
	{
		map gfx/2d/objArrow.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

ui/assets/filter_nxac_loading
{
    nomipmaps

    {
        map ui/assets/filter_nxac_loading.tga
        blendfunc blend
    }

}

