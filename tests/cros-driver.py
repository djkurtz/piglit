# Copyright (c) 2014 The Chromium OS Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
# -*- coding: utf-8 -*-

from tests.gpu import profile

__all__ = ['profile']

# These don't test the driver
del profile.tests['glslparsertest']

# These take too long
del profile.tests['glean']['blendFunc']
del profile.tests['glean']['depthStencil']
del profile.tests['glean']['pointAtten']
del profile.tests['spec']['!OpenGL 1.1']['streaming-texture-leak']

# IHF: this test runs with too much memory on my 64 bit dev system
del profile.tests['spec']['!OpenGL 1.2']['tex3d-maxsize']

# IHF: this test hangs testing
del profile.tests['spec']['!OpenGL 1.1']['longprim']
del profile.tests['glx']['glx-make-glxdrawable-current']
del profile.tests['shaders']['glsl-texcoord-array']

# IHF: bug 19813 - x86-generic crashes/hangs blacklisted (roughly declining order of badness)
del profile.tests['spec']['glsl-1.10']['execution']['samplers']['in-parameter']
del profile.tests['spec']['glsl-1.10']['execution']['samplers']['in-parameter-struct']
del profile.tests['spec']['glsl-1.10']['execution']['samplers']['normal-parameter']
del profile.tests['spec']['glsl-1.10']['execution']['samplers']['normal-parameter-struct']

# IHF: This test crashed on lumpy during checkout.
del profile.tests['spec']['!OpenGL 1.1']['max-texture-size']

# IHF: These tests cause hangchecks on lumpy/stumpy and often many crashes and a loss
# of hardware acceleration later. See crosbug.com/30809.
del profile.tests['spec']['glsl-1.30']['execution']['fs-discard-exit-1']
del profile.tests['spec']['glsl-1.30']['execution']['fs-discard-exit-2']

# SCBA: These crashed on Sandy Bridge. Some are not supported.
del profile.tests['spec']['ARB_framebuffer_object']['negative-readpixels-no-rb']
del profile.tests['spec']['ARB_uniform_buffer_object']['maxuniformblocksize/fsexceed']
del profile.tests['spec']['ARB_uniform_buffer_object']['maxuniformblocksize/fs']
del profile.tests['spec']['EGL_KHR_create_context']
del profile.tests['spec']['EGL_NOK_swap_region']
del profile.tests['spec']['EGL_NOK_texture_from_pixmap']
del profile.tests['spec']['EGL 1.4']
del profile.tests['spec']['EXT_texture_array']['compressed teximage']
del profile.tests['spec']['EXT_packed_depth_stencil']['fbo-clear-formats stencil']
del profile.tests['spec']['EXT_texture_compression_s3tc']['s3tc-errors']
del profile.tests['spec']['glsl-1.10']['execution']['varying-packing']
del profile.tests['spec']['ARB_draw_elements_base_vertex']['draw-elements-base-vertex-neg-user_varrays']
del profile.tests['spec']['glsl-1.30']['execution']['varying-packing-mixed-types']

# SCBA: These crashed on i915
del profile.tests['shaders']['glsl-fs-convolution-2']

# DB: these hang on SNB with HiZ disabled, crbug.com/313085
del profile.tests['spec']['EXT_framebuffer_multisample']
del profile.tests['spec']['!OpenGL 1.1']['copyteximage 2D']
del profile.tests['spec']['ARB_texture_rectangle']['copyteximage RECT']
