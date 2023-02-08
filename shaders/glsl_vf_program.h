#pragma once

#include <string>
#include <string_view>

#include <glad/glad.h>

namespace shader {

/* ------------------------------------------------------------------------------------------------------------------
 * Basic GLSL program class for working with vertex and fragment shaders only.
 *
 * This class only supports loading shader source code from the filesystem; a more robust implementation would be
 * to supply a "source" to the Init(...) method that would allow the source code to be obtained from anywhere.
 *-----------------------------------------------------------------------------------------------------------------*/
class GlslVFProgram final {
public:
  GlslVFProgram() noexcept;

  GlslVFProgram(const GlslVFProgram&) = delete;
  GlslVFProgram& operator=(const GlslVFProgram&) = delete;
  GlslVFProgram(GlslVFProgram&&) = delete;
  GlslVFProgram& operator=(GlslVFProgram&&) = delete;

  ~GlslVFProgram();

  bool Init(const std::string& vertex_shader_path, const std::string& fragment_shader_path);

  void UseProgram();

  void DeleteProgram();

private:
  bool GetShaderSourceFromFilesystem(std::string_view path, std::string& out_source);

  bool CompileShader(GLenum shader_type, const char* source, GLuint& out_shader_id);
  bool LinkProgram();

  GLuint vertex_shader_id_ = 0;
  GLuint fragment_shader_id_ = 0;
  GLuint program_id_ = 0;

  bool did_delete_program_ = false;
};

}
