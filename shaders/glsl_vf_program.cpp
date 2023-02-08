#include "glsl_vf_program.h"

#include <fstream>
//#include <iostream> // TODO: Remove this if this class doesn't write to std::cerr
#include <sstream>

namespace shader {

GlslVFProgram::GlslVFProgram() noexcept { }

// TODO: If Init(...) will return error codes, we probably want to use an enum instead of ints.
int GlslVFProgram::Init(const std::string& vertex_shader_path, const std::string& fragment_shader_path) {
  bool success = false;
  std::string source;

  success = GetShaderSourceFromFilesystem("", source);
  if (!success) {
    return 1;
  }

  success = CompileShader();

  return 0;
}

// TODO: Implement
void GlslVFProgram::UseProgram() {
  //
}

// TODO: Do we want to use out_source to return an error message, too?
bool GlslVFProgram::GetShaderSourceFromFilesystem(std::string_view path, std::string& out_source) {
  std::ifstream input_stream;
  input_stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    input_stream.open(path.data(), std::ios_base::in);

    std::stringstream source_stream;
    source_stream << input_stream.rdbuf();
    input_stream.close();
    out_source = source_stream.str();

    return true;
  } catch (std::ios_base::failure& e) {
    //std::cerr << "Unable to load shader: " << path << " " << e.what() << " error code: " << e.code() << "\n";
    return false;
  }
}

// TODO: Implement
bool GlslVFProgram::CompileShader() {
  return false;
}

// TODO: Implement
bool GlslVFProgram::LinkShader() {
  return false;
}

}
