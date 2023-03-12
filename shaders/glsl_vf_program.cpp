#include "glsl_vf_program.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace shader {

GlslVFProgram::GlslVFProgram() noexcept { }

GlslVFProgram::~GlslVFProgram() {
  DeleteProgram();
}

bool GlslVFProgram::Init(const std::string& vertex_shader_path, const std::string& fragment_shader_path) {
  bool success = false;
  std::string source;

  success = GetShaderSourceFromFilesystem(vertex_shader_path, source);
  if (!success) {
    return false;
  }
  success = CompileShader(GL_VERTEX_SHADER, source.c_str(), vertex_shader_id_);
  if (!success) {
    return false;
  }

  success = GetShaderSourceFromFilesystem(fragment_shader_path, source);
  if (!success) {
    return false;
  }
  success = CompileShader(GL_FRAGMENT_SHADER, source.c_str(), fragment_shader_id_);
  if (!success) {
    return false;
  }

  LinkProgram();

  source.clear();

  return true;
}

// TODO: Implement
void GlslVFProgram::UseProgram() {
  glUseProgram(program_id_);
}

void GlslVFProgram::DeleteProgram() {
  if (!did_delete_program_) {
    glDeleteProgram(program_id_);
    did_delete_program_ = true;
  }
}

bool GlslVFProgram::GetShaderSourceFromFilesystem(std::string_view path, std::string& out_source) {
  std::ifstream input_stream(path.data());
  if (input_stream.is_open()) {
    input_stream.open(path.data(), std::ios_base::in);

    std::stringstream source_stream;
    source_stream << input_stream.rdbuf();
    input_stream.close();
    out_source = source_stream.str();

    return true;
  } else {
    std::cerr << "Unable to load shader: " << path << "\n";
    return false;
  }
}

bool GlslVFProgram::CompileShader(GLenum shader_type, const char* source, GLuint& out_shader_id) {
  bool success = false;

  out_shader_id = glCreateShader(shader_type);

  glShaderSource(
    out_shader_id,  // ID of the shader to compile
    1,              // number of lines of shader code
    &source,        // reference to source code
    nullptr         // source code is null terminated
  );

  glCompileShader(out_shader_id);

  GLint did_compile = 0;
  glGetShaderiv(out_shader_id, GL_COMPILE_STATUS, &did_compile);
  if (did_compile == GL_TRUE) {
    success = true;
  } else {
    GLint log_length = 0;
    glGetShaderiv(out_shader_id, GL_INFO_LOG_LENGTH, &log_length);

    GLchar* log = new GLchar[log_length];
    glGetShaderInfoLog(out_shader_id, log_length, nullptr, log);

    std::cerr << "Unable to compile shader: " << log << "\n";

    delete[] log;
    glDeleteShader(out_shader_id);
  }

  return success;
}

bool GlslVFProgram::LinkProgram() {
  bool success = false;

  program_id_ = glCreateProgram();
  glAttachShader(program_id_, vertex_shader_id_);
  glAttachShader(program_id_, fragment_shader_id_);
  glLinkProgram(program_id_);

  GLint did_link = 0;
  glGetProgramiv(program_id_, GL_LINK_STATUS, &did_link);
  if (did_link == GL_TRUE) {
    success = true;
  } else {
    GLint log_length = 0;
    glGetProgramiv(program_id_, GL_INFO_LOG_LENGTH, &log_length);

    GLchar* log = new GLchar[log_length];
    glGetProgramInfoLog(program_id_, log_length, nullptr, log);

    std::cerr << "Unable to link shader: " << log << "\n";

    delete[] log;
  }

  glDeleteShader(vertex_shader_id_);
  glDeleteShader(fragment_shader_id_);

  return success;
}

}
