#include "Shader.h"

Shader::Shader() : shaderID(0)
{
	memset(shaders, 0, sizeof(shaders));
	memset(uniforms, 0, sizeof(uniforms));
}

void Shader::init(const std::string& glslPath)
{
	std::string shaderFile = LoadShader(glslPath);
	for (size_t i = 0; i < (int)ShaderType::SH_Max; i++)
	{
		size_t indicator = shaderFile.find("#ifdef");
		if (indicator != std::string::npos)
		{

			size_t endPos = shaderFile.find("#endif");
			assert(endPos != std::string::npos && "#endif missing in shader");

			std::string subGLSLstring = shaderFile.substr(indicator, endPos - indicator);

			std::string vertexType;
			ShaderType type = ShaderType::SH_Max;
			if (subGLSLstring.find("#ifdef vertex") != std::string::npos) {
				vertexType = "#ifdef vertex";
				type = ShaderType::SH_Vertex;
			}
			else if (subGLSLstring.find("#ifdef fragment") != std::string::npos) {
				vertexType = "#ifdef fragment";
				type = ShaderType::SH_Frag;
			}
			else if (subGLSLstring.find("#ifdef geometry") != std::string::npos) {
				vertexType = "#ifdef geometry";
				type = ShaderType::SH_Geometry;

			}


			std::string clearShaderBloc = subGLSLstring.substr(vertexType.length());
			shaders[(int)type] = Compile(clearShaderBloc.c_str(), type, clearShaderBloc.length());
			shaderFile = shaderFile.substr(endPos + sizeof("#endif"));
			//LOG("%d", indicator);
		}
	}

	shaderID = glCreateProgram();
	for (size_t i = 0; i < static_cast<int>(ShaderType::SH_Max); i++)
	{
		glAttachShader(shaderID, shaders[i]);
	}

	glLinkProgram(shaderID);

	int success;
	char infoLog[512];
	glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
		//LOG("Error linking shader program: %s", infoLog);
	}

	for (size_t i = 0; i < static_cast<int>(ShaderType::SH_Max); i++)
	{
		glDetachShader(shaderID, shaders[i]);
	}

	for (size_t i = 0; i < static_cast<int>(ShaderType::SH_Max); i++)
	{
		glDeleteShader(shaders[i]);
		shaders[i] = 0;
	}
	//RELEASE_ARRAY(vertex);
	//RELEASE_ARRAY(fragment);
	//RELEASE_ARRAY(fileBuffer);



	//shaders[0] = CreateShader(LoadShader(vertFile), GL_VERTEX_SHADER); // create vertex shader
	//shaders[1] = CreateShader(LoadShader(fragFile), GL_FRAGMENT_SHADER); // create fragment shader
	//shaders[2] = CreateShader(LoadShader(geoShader), GL_GEOMETRY_SHADER); // create fragment shader

	//for (unsigned int i = 0; i < NUM_SHADERS; i++)
	//{
	//	glAttachShader(shaderID, shaders[i]); //add all our shaders to the shader program "shaders" 
	//}

	//glBindAttribLocation(shaderID, 0, "VertexPosition"); // associate attribute variable with our shader program attribute (in this case attribute vec3 position;)
	//glBindAttribLocation(shaderID, 1, "VertexTexCoord");
	//glBindAttribLocation(shaderID, 2, "VertexNormal");

	//glLinkProgram(shaderID); //create executables that will run on the GPU shaders
	//CheckShaderError(shaderID, GL_LINK_STATUS, true, "Error: Shader program linking failed"); // cheack for error

	//glValidateProgram(shaderID); //check the entire program is valid
	//CheckShaderError(shaderID, GL_VALIDATE_STATUS, true, "Error: Shader program not valid");

	uniforms[TRANSFORM_U] = glGetUniformLocation(shaderID, "transform"); // associate with the location of uniform variable within a program
}

GLuint Shader::Compile(const char* fileBuffer, ShaderType type, const GLint size)
{
	GLuint compileShader = 0;
	compileShader = glCreateShader(GetTypeMacro(type));
	glShaderSource(compileShader, 1, &fileBuffer, &size);
	glCompileShader(compileShader);

	int success = 0;
	char infoLog[512];
	glGetShaderiv(compileShader, GL_COMPILE_STATUS, &success);
	if (success == 0)
	{
		glGetShaderInfoLog(compileShader, 512, NULL, infoLog);

		if (type == ShaderType::SH_Vertex)
		{
			////LOG("Error compilating vertex shader: %s", infoLog);
		}
		else {
			////LOG("Error compilating fragment shader: %s", infoLog);
		}
		glDeleteShader(compileShader);

		//#ifndef STANDALONE
		//		W_TextEditor* textEditorWindow = static_cast<W_TextEditor*>(EngineExternal->moduleEditor->GetEditorWindow(EditorWindow::TEXTEDITOR));
		//		textEditorWindow->SetErrorsOnScreen(infoLog);
		//#endif // !STANDALONE


		return 0;
	}

	return compileShader;
}

int Shader::GetTypeMacro(ShaderType type)
{
	int ret = 0;
	switch (type)
	{
	case ShaderType::SH_Vertex:
		ret = GL_VERTEX_SHADER;
		break;
	case ShaderType::SH_Frag:
		ret = GL_FRAGMENT_SHADER;
		break;
	case ShaderType::SH_Geometry:
		ret = GL_GEOMETRY_SHADER;
		break;
	case ShaderType::SH_Max:
		ret = 0;
		break;
	default:
		ret = 0;
		break;
	}

	return ret;
}


Shader::~Shader()
{
	for (unsigned int i = 0; i < static_cast<int>(ShaderType::SH_Max); i++)
	{
		glDetachShader(shaderID, shaders[i]); //detach shader from program
		glDeleteShader(shaders[i]); //delete the sahders
	}
	glDeleteProgram(shaderID); // delete the program
}

void Shader::Bind()
{
	glUseProgram(shaderID); //installs the program object specified by program as part of rendering state
}

void Shader::Update(const Transform& transform, const Camera& camera)
{
	glm::mat4 mvp = camera.getViewProjection() * transform.GetModel();
	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GLU_FALSE, &mvp[0][0]);
}


GLuint Shader::CreateShader(const std::string& text, unsigned int type)
{
	GLuint shader = glCreateShader(type); //create shader based on specified type

	if (shader == 0) //if == 0 shader no created
		std::cerr << "Error type creation failed " << type << std::endl;

	const GLchar* stringSource[1]; //convert strings into list of c-strings
	stringSource[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, stringSource, lengths); //send source code to opengl
	glCompileShader(shader); //get open gl to compile shader code

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!"); //check for compile error

	return shader;
}

std::string Shader::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

