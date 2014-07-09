/*
 * Copyright © 2010 Intel Corporation
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
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/**
 * \file createshaderprogram-bad-type.c
 * Call glCreateShaderProgramEXT with various program types, verify results
 *
 * \author Ian Romanick <ian.d.romanick@intel.com>
 */
#include "piglit-util-gl.h"

PIGLIT_GL_TEST_CONFIG_BEGIN

	config.supports_gl_compat_version = 10;

	config.window_visual = PIGLIT_GL_VISUAL_RGB | PIGLIT_GL_VISUAL_DOUBLE;

PIGLIT_GL_TEST_CONFIG_END

static const char vs_text[] =
	"void main() { gl_Position = gl_Vertex; }";

static const char gs_text[] =
	"#extension GL_EXT_geometry_shader4: enable\n"
	"#extension GL_ARB_geometry_shader4: enable\n"
	"void main() {\n"
	"    for(int i = 0; i < gl_VerticesIn; i++) {\n"
	"        gl_Position = gl_PositionIn[i];\n"
	"        EmitVertex();\n"
	"    }\n"
	"    EndPrimitive();\n"
	"}\n"
	;

static const char fs_text[] =
	"void main() { gl_FragColor = vec4(0.0); }";

enum piglit_result
piglit_display(void)
{
	return PIGLIT_FAIL;
}

GLboolean
try_CreateShaderProgram(GLenum type, const char *source, GLenum expect)
{
	GLboolean pass = GL_TRUE;
	GLenum err;
	GLuint prog;

	/* There shouldn't be any GL errors, but clear them all just to be
	 * sure.
	 */
	while (glGetError() != 0)
		/* empty */ ;

	/* Type is not one of the known shader types.  This should generate
	 * the error GL_INVALID_ENUM.
	 */
	prog = glCreateShaderProgramEXT(type, source);

	err = glGetError();
	if (err != expect) {
		printf("Unexpected OpenGL error state 0x%04x for "
		       "glCreateShaderProgramEXT called with\n"
		       "the %sshader target 0x%04x (expected 0x%04x).\n",
		       err, (expect == 0) ? "" : "invalid ", type, expect);
		pass = GL_FALSE;
	}

	while (glGetError() != 0)
		/* empty */ ;

	/* Exactly one of expect or prog should be zero.  If the caller expected
	 * an error (expect != 0), a program should not have been created.  If
	 * the caller expected success, a program should have been created.
	 */
	if ((expect == 0) != (prog != 0)) {
		printf("Expected that a program would %sbe created, "
		       "but instead one was %screated.\n",
		       (expect == 0) ? "not " : "",
		       (prog == 0) ? "not " : "");
		pass = GL_FALSE;
	}

	return pass;
}

void
piglit_init(int argc, char **argv)
{
	const GLenum expect = (piglit_is_extension_supported("GL_ARB_geometry_shader4")
			       || piglit_is_extension_supported("GL_EXT_geometry_shader4")
			       || piglit_is_extension_supported("GL_NV_geometry_shader4"))
		? 0 : GL_INVALID_ENUM;
	GLboolean pass;

	piglit_require_gl_version(20);

	piglit_require_extension("GL_EXT_separate_shader_objects");

	pass = try_CreateShaderProgram(GL_PROXY_TEXTURE_3D, vs_text,
				       GL_INVALID_ENUM);
	pass = try_CreateShaderProgram(GL_VERTEX_SHADER, vs_text, 0)
		&& pass;
	pass = try_CreateShaderProgram(GL_FRAGMENT_SHADER, fs_text, 0)
		&& pass;
	pass = try_CreateShaderProgram(GL_GEOMETRY_SHADER_ARB, gs_text, expect)
		&& pass;

	piglit_report_result(pass ? PIGLIT_PASS : PIGLIT_FAIL);
}
