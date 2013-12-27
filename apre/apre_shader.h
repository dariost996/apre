#if defined _APRE_H_
#ifndef _APRE_SHADER_H_
#define _APRE_SHADER_H_

/**
    A class for use GLSL shaders

    <br><br>Usage:<br><br>
    apreShader* shader=new apreShader();<br>
    shader->addVertexShaderFromString("vertex.glsl");<br>
    shader->addFragmentShaderFromString("fragment.glsl");<br>
    shader->compileShader();<br>
    shader->useShader();<br>
*/

class apreShader
{
protected:
    std::vector<GLhandleARB> vertex;
    std::vector<GLhandleARB> fragment;
    GLhandleARB program;
    bool compiled;
    bool read_file(std::vector<char>& v, const char* file_name)
    {
        using namespace std;
        FILE* f=fopen(file_name, "r");
        if(!f) return false;
        v.clear();
        char buffer[4096];
        while(!feof(f))
        {
            size_t dim=fread(buffer, sizeof(char), 4096, f);
            v.insert(v.end(), buffer, buffer+dim);
        }
        v.push_back('\0');
        fclose(f);
        return true;
    }
public:
    ~apreShader()
    {
        for(uint64_t i=0; i<vertex.size(); i++)
        {
            glDetachObjectARB(program, vertex[i]);
            glDeleteObjectARB(vertex[i]);
        }
        for(uint64_t i=0; i<fragment.size(); i++)
        {
            glDetachObjectARB(program, fragment[i]);
            glDeleteObjectARB(vertex[i]);
        }
        glDeleteObjectARB(program);
        fragment.clear();
        vertex.clear();
    }
    GLhandleARB getProgram()
    {
        return program;
    }                                                       ///< Return the handler of the shader
    bool addVertexShaderFromString(const char* ss);         ///< ss is the NULL-terminated string. Return false on failure and true on success
    bool addFragmentShaderFromString(const char* ss);       ///< ss is the NULL-terminated string. Return false on failure and true on success
    bool addVertexShaderFromFile(const char* fileName);     ///< fileName is the path to the file. Return false on failure and true on success
    bool addFragmentShaderFromFile(const char* fileName);   ///< fileName is the path to the file. Return false on failure and true on success
    bool compileShader();       ///< Return false on failure and true on success
    bool useShader();           ///< Return false on failure and true on success
    bool isCompiled()
    {
        return compiled;
    }                           ///< Return true if the shader is compiled, false otherwise
    apreShader()
    {
        if(!glewIsSupported("GL_ARB_vertex_shader") ||
           !glewIsSupported("GL_ARB_fragment_shader") ||
           !glewIsSupported("GL_ARB_vertex_program") ||
           !glewIsSupported("GL_ARB_fragment_program") ||
           !glewIsSupported("GL_ARB_shader_objects"))
        (*apreErrFunc)(2, "Shaders are not supported");
        compiled=false;
    }
};

bool apreShader::useShader()
{
    if(!compiled)
    {
        (*apreErrFunc)(1, "This shader is not compiled");
        return false;
    }
    glUseProgramObjectARB(program);
    return true;
}

bool apreShader::compileShader()
{
    program=glCreateProgramObjectARB();
    for(uint64_t i=0; i<vertex.size(); i++)
    {
        glAttachObjectARB(program, vertex[i]);
    }
    for(uint64_t i=0; i<fragment.size(); i++)
    {
        glAttachObjectARB(program, fragment[i]);
    }
    glLinkProgramARB(program);
    GLint a;
    glGetObjectParameterivARB(program, GL_OBJECT_LINK_STATUS_ARB, &a);
    if(!a)
    {
        char* s=(char*)malloc(4096);
        char* s2=(char*)malloc(4096);
        int len;
        glGetInfoLogARB(program, 4096, &len, s);
        //fprintf(stderr, "Link error: %s", s);
        snprintf(s2, 4096, "This shader can't be compiled - %s", s);
        free(s);
        (*apreErrFunc)(1, s2);
        free(s2);
        return false;
    }
    compiled=true;
    return true;
}

bool apreShader::addVertexShaderFromFile(const char* fileName)
{
    using namespace std;
    vector<char> v;
    GLhandleARB temp;
    vertex.push_back(temp);
    vertex[vertex.size()-1]=glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
    char* p;
    if(!read_file(v, fileName))
    {
        //fprintf(stderr, "Unable to open %s\n", fileName);
        char sss[4096];
        snprintf(sss, 4096, "Unable to open %s", fileName);
        (*apreErrFunc)(2, sss);
        return false;
    }
    //v[v.size()-1]='\0';
    p=v.data();
    glShaderSourceARB(vertex[vertex.size()-1], 1, (const char**)&p, NULL);
    glCompileShaderARB(vertex[vertex.size()-1]);
    GLint a;
    glGetObjectParameterivARB(vertex[vertex.size()-1], GL_OBJECT_COMPILE_STATUS_ARB, &a);
    v.clear();
    if(!a)
    {
        char* s=(char*)malloc(4096);
        char ss[4096];
        glGetInfoLogARB(vertex[vertex.size()-1], 4096, nullptr, s);
        snprintf(ss, 4096, "%s error: %s", fileName, s);
        free(s);
        (*apreErrFunc)(1, ss);
        return false;
    }
    return true;
}

bool apreShader::addVertexShaderFromString(const char* ss)
{
    using namespace std;
    GLhandleARB temp;
    vertex.push_back(temp);
    vertex[vertex.size()-1]=glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
    glShaderSourceARB(vertex[vertex.size()-1], 1, (const char**)&ss, NULL);
    glCompileShaderARB(vertex[vertex.size()-1]);
    GLint a;
    glGetObjectParameterivARB(vertex[vertex.size()-1], GL_OBJECT_COMPILE_STATUS_ARB, &a);
    if(!a)
    {
        char* s=(char*)malloc(4096);
        char ss[4096];
        glGetInfoLogARB(vertex[vertex.size()-1], 4096, nullptr, s);
        snprintf(ss, 4096, "%s error: %s", ss, s);
        free(s);
        (*apreErrFunc)(1, ss);
        return false;
    }
    return true;
}

bool apreShader::addFragmentShaderFromFile(const char* fileName)
{
    using namespace std;
    vector<char> v;
    GLhandleARB temp;
    fragment.push_back(temp);
    fragment[fragment.size()-1]=glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
    char* p;
    if(!read_file(v, fileName))
    {
        //fprintf(stderr, "Unable to open %s\n", fileName);
        char sss[4096];
        snprintf(sss, 4096, "Unable to open %s", fileName);
        (*apreErrFunc)(2, sss);
        return false;
    }
    //v[v.size()-1]='\0';
    p=v.data();
    glShaderSourceARB(fragment[fragment.size()-1], 1, (const char**)&p, NULL);
    glCompileShaderARB(fragment[fragment.size()-1]);
    GLint a;
    glGetObjectParameterivARB(fragment[fragment.size()-1], GL_OBJECT_COMPILE_STATUS_ARB, &a);
    v.clear();
    if(!a)
    {
        char* s=(char*)malloc(4096);
        char ss[4096];
        glGetInfoLogARB(fragment[fragment.size()-1], 4096, nullptr, s);
        snprintf(ss, 4096, "%s error: %s", fileName, s);
        free(s);
        (*apreErrFunc)(1, ss);
        return false;
    }
    return true;
}

bool apreShader::addFragmentShaderFromString(const char* ss)
{
    using namespace std;
    GLhandleARB temp;
    fragment.push_back(temp);
    fragment[fragment.size()-1]=glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
    glShaderSourceARB(fragment[fragment.size()-1], 1, (const char**)&ss, NULL);
    glCompileShaderARB(fragment[fragment.size()-1]);
    GLint a;
    glGetObjectParameterivARB(fragment[fragment.size()-1], GL_OBJECT_COMPILE_STATUS_ARB, &a);
    if(!a)
    {
        char* s=(char*)malloc(4096);
        char ss[4096];
        glGetInfoLogARB(fragment[fragment.size()-1], 4096, nullptr, s);
        snprintf(ss, 4096, "%s error: %s", ss, s);
        free(s);
        (*apreErrFunc)(1, ss);
        return false;
    }
    return true;
}


#endif
#endif
