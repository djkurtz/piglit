/*
 * Copyright © 2011 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *    Chad Versace <chad.versace@intel.com>
 */

/**
 * \file hiz-depth-stencil-test-fbo-d0-s8.c
 *
 * Check that rendering to an FBO works correctly when depth and stencil test
 * are simultaneously enabled and the following attachments are present:
 *     - GL_COLOR_ATTACHMENT0: GL_RGBA
 *     - GL_STENCIL_ATTACHMENT: GL_STENCIL_INDEX8
 *
 * This test probes only the color buffer; it does not probe the stencil
 * nor the depth buffer.
 *
 * \author Chad Versace <chad.versace@intel.com>
 */

#include "piglit-util-gl.h"
#include "hiz/hiz-util.h"

PIGLIT_GL_TEST_CONFIG_BEGIN

	config.supports_gl_compat_version = 10;
	config.window_visual = PIGLIT_GL_VISUAL_RGB;

PIGLIT_GL_TEST_CONFIG_END

struct hiz_fbo_options fbo_options = {
	GL_RGBA,
	0,
	GL_STENCIL_INDEX8,
	0,
};

void
piglit_init(int argc, char **argv)
{
	/* empty */
}

enum piglit_result
piglit_display()
{
	if (hiz_run_test_depth_stencil_test_fbo(&fbo_options))
		return PIGLIT_PASS;
	else
		return PIGLIT_FAIL;
}
