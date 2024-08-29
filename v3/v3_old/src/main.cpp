#include <scop.hpp>
#include <math.h>

extern float triDecx;
extern float triDecy;
extern float triDecz;

int main_loop(t_env *env){

    Shader shaderOb1("./shaders/vertSimple.txt", "./shaders/fragSimple.txt");
    Shader shaderOb2("./shaders/vertChooseCol.txt", "./shaders/fragSimpleBlu.txt");

    float verticles[] = {
         0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
         0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f
    };
    unsigned int indices[] = {
        0, 1, 2,
        0, 1, 3
    };
    unsigned int indices2[] = {
        1, 2, 4,
        1, 3, 5
    };



    // Lier le VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Copier les sommets dans un tampon VBO pour OpenGL
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticles), verticles, GL_STATIC_DRAW);

    // Copier les indices dans un tampon EBO pour OpenGL
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Initialiser les attributs de sommet
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Initialiser les attributs de couleur
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    unsigned int VAO2;
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);

    // Copier les sommets dans un tampon VBO pour OpenGL
    unsigned int VBO2;
    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticles), verticles, GL_STATIC_DRAW);

    // Copier les indices dans un tampon EBO pour OpenGL
    unsigned int EBO2;
    glGenBuffers(1, &EBO2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

    // Initialiser les attributs de sommet
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();

        processInputs(env);

        shaderOb1.use();
        shaderOb1.setFloat("decalx", triDecx);
        shaderOb1.setFloat("decaly", triDecy);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        shaderOb2.use();
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue*2) / 2.0f) + 0.5f;
        float blueValue = (-sin(timeValue*2) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderOb2.getID(), "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, blueValue, 1.0f);
        glBindVertexArray(VAO2);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(env->window);

    } while( glfwWindowShouldClose(env->window) == 0 );

    return 0;
}

int main(){
    t_env env;

    (void)env;


    initOpenGl(&env);

    main_loop(&env);

    cleanOpenGl(&env);

    return 0;
}