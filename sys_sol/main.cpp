#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <vector>
#include <cstdlib>

#include "vertexbuffer.h"
#include "vertexarray.h"
#include "shader.h"
#include "renderer.h"
#include "camera.h"
#include "navigationcontrols.h"
#include "pointlight.h"

using namespace std;

int main()
{
    string path = "/home/formation/open_gl/sys_sol";
    const char *pathc = "/home/formation/open_gl/sys_sol";
/////////////////////////Initialisation de GLFW/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if(!glfwInit()){
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }


    glfwWindowHint(GLFW_SAMPLES, 4); //antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //version core

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);


/////////////////////////Ouverture de la fenêtre/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //définition de la taille de la fenêtre
    int width=600;
    int height=600;

    //On récupère les dimensions de l'écran pour créer la fenètre
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    glfwGetMonitorWorkarea(primary,nullptr,nullptr, &width, &height);

    //Enfin on crée la fenêtre
    GLFWwindow* window = glfwCreateWindow(width,height,"OpenGL_API",NULL,NULL);
    glfwSwapInterval(1);
    //On vérifie que l'initialisation a bien marché
    if (window==NULL){
        fprintf(stderr, "Erreur lors de la création de la fénêtre\n");
        glfwTerminate();
        return -1;
    }

    //Enfin on définit la fenêtre créée comme la fenêtre sur laquelle on va dessiner
    glfwMakeContextCurrent(window);



/////////////////////////Initialisation de GLEW/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Initialisation de GLEW
    glewExperimental=true;
    if (glewInit() != GLEW_OK){
        fprintf(stderr, "Erreur lors de l'initialisation de GLEW\n");
        return -1;
    }

/////////////////////////On crée un Renderer/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Renderer renderer;


/////////////////////////On crée un Shader/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Shader shader(path+"/shaders/SimpleVertexShader.vertexshader", path+"/shaders/SimpleFragmentShader.fragmentshader");
    shader.Bind();
    shader.setUniform1f("SunCoef",1);

/////////////////////////On crée un vertex array/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    VertexArray va;
    va.Bind();

/////////////////////////On crée la camera et les contrôles/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    float SpeedCoef = 0.5;
    Camera cam(width, height);
    cam.position = glm::vec3(0.f,150.f,150.f);
    NavigationControls controls(window, &cam);
    PointLight Lumiere = PointLight(glm::vec3(0.8,0.8,0.8),glm::vec3(0.f,500.f,0.f),1);

/////////////////////////Création des formes à afficher/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    vector<glm::vec3> orbitVertices;
    vector<glm::vec2> orbitUvs;
    for(int i =0;i < 500; i++){
        float theta = 2.f * 3.1415926f * float(i) / 500.f;
        float x = cosf(theta);
        float y = sinf(theta);
        float u = 0.5f * cosf(theta) + 0.5f;
        float v  =0.5f * sinf(theta) + 0.5f;
        orbitVertices.push_back(glm::vec3(x,0.f,y));
        orbitUvs.push_back(glm::vec2(u,v));
    }

    //Chemins des différents fichiers .obj utilisés
    const char *sphere = "/home/formation/open_gl/sys_sol/obj/planete.obj";
    const char *cube = "/home/formation/open_gl/sys_sol/obj/cube.obj";
    const char *orbite = "/home/formation/open_gl/sys_sol/obj/orbite_50.obj";
    const char *anneau = "/home/formation/open_gl/sys_sol/obj/anneau.obj";

    //Création de tous les objets correspondants aux planètes, àl'anneau de Saturne et à la Lune
    Object Soleil(sphere,path+"/textures/planets/2k_sun.jpg");
    Object Mercure(sphere,path+"/textures/planets/2k_mercury.jpg");
    Object Venus(sphere, path+"/textures/planets/2k_venus.jpg");
    Object Terre(sphere,path+"/textures/planets/earth2k.jpg");
    Object Lune(sphere,path+"/textures/planets/2k_moon.jpg");
    Object Mars(sphere,path+"/textures/planets/2k_mars.jpg");
    Object Jupiter(sphere,path+"/textures/planets/2k_jupiter.jpg");
    Object Saturne(sphere,path+"/textures/planets/2k_saturn.jpg");
    Object Anneau(anneau,path+"/textures/planets/2k_saturn_ring_turned.png");
    Object Uranus(sphere,path+"/textures/planets/2k_uranus.jpg");
    Object Neptune(sphere,path+"/textures/planets/2k_neptune.jpg");

    // Création de la skybox
    Object skybox(cube,path+"/textures/space/8k_space.jpg");
    //Object Orbite(orbitVertices,orbitUvs,path+"/textures/rouge.png");
    Object Orbite(orbite,path+"/textures/marbre.png");

    /*std::vector<glm::vec2> StartPos = {};
    StartPos.push_back(float x rand() % 6);*/


/////////////////////////Création de la matrice MVP/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    cam.computeMatrices(width, height);
    glm::mat4 m = Soleil.getModelMatrix();
    glm::mat4 v = cam.getViewMatrix();
    glm::mat4 p = cam.getProjectionMatrix();

    glm::mat4 mvp = p*v*m;

    //shader.setUniformMat4f("MVP", mvp);

/////////////////////////Boucle de rendu/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // Assure que l'on peut capturer les touche de clavier
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    //On indique la couleur de fond
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    //On autorise les tests de profondeur

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);


    float lastTime = glfwGetTime();
    float currentTime, deltaTime;

    while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)){

        renderer.Clear();
        shader.Bind();
        Lumiere.Bind(shader);
        currentTime = glfwGetTime();
        deltaTime = currentTime-lastTime;
        lastTime = currentTime;
        controls.setSpeed(100);
        float PlanetSpeed = currentTime*SpeedCoef;

        controls.update(deltaTime, &shader,SpeedCoef);
        shader.setUniform3fv("posCam",cam.position);


        //Mercure
        cam.computeMatrices(width, height);
        //On donne une vitesse de rotation à l'objet
        Mercure.rotationAngles.y=PlanetSpeed*0.02;
        // On donne également des coordonnées mobiles pour la révolution autour du soleil
        Mercure.position = glm::vec3(200*cos(PlanetSpeed + 4.28),0.f,200*sin(PlanetSpeed + 4.28));
        m = Mercure.getModelMatrix();
        glm::mat4 m_scale = glm::scale(glm::mat4(1.f),glm::vec3(10.f,10.f,10.f));
        m = m * m_scale;
        v = cam.getViewMatrix();
        p = cam.getProjectionMatrix();
        mvp = p*v*m;
        shader.setUniformMat4f("MVP", mvp);
        shader.setUniformMat4f("m",m);
        shader.setUniform1f("SunCoef",1);
        renderer.Draw(va, Mercure, shader);

        //Venus
        cam.computeMatrices(width, height);
        Venus.rotationAngles.y=PlanetSpeed*0.01;
        Venus.position = glm::vec3(300*cos(PlanetSpeed*0.75 + 2.74),0.f,300*sin(PlanetSpeed*0.75 + 2.74));
        m = Venus.getModelMatrix();
        m_scale = glm::scale(glm::mat4(1.f),glm::vec3(12.f,12.f,12.f));
        m = m * m_scale;
        v = cam.getViewMatrix();
        p = cam.getProjectionMatrix();
        mvp = p*v*m;
        shader.setUniformMat4f("MVP", mvp);
        shader.setUniformMat4f("m",m);
        renderer.Draw(va, Venus, shader);

        //Terre
        cam.computeMatrices(width, height);
        Terre.rotationAngles.y=PlanetSpeed;
        Terre.position = glm::vec3(400*cos(PlanetSpeed*0.55 + 4.55),0.f,400*sin(PlanetSpeed*0.55 + 4.55));
        m = Terre.getModelMatrix();
        m_scale = glm::scale(glm::mat4(1.f),glm::vec3(11.8f,11.8f,11.8f));
        m = m * m_scale;
        v = cam.getViewMatrix();
        p = cam.getProjectionMatrix();
        mvp = p*v*m;
        shader.setUniformMat4f("MVP", mvp);
        shader.setUniformMat4f("m",m);
        renderer.Draw(va, Terre, shader);

        /*Orbite.position = glm::vec3(0.f,0.f,0.f);
        m = Orbite.getModelMatrix();
        m_scale = glm::scale(glm::mat4(1.f),glm::vec3(2.f,2.f,2.f));
        m = m * m_scale;
        v = cam.getViewMatrix();
        p = cam.getProjectionMatrix();
        mvp = p*v*m;
        shader.setUniformMat4f("MVP",mvp);
        renderer.Draw(va,Orbite,shader);

        m = Orbite.getModelMatrix();
        m_scale = glm::scale(glm::mat4(1.f),glm::vec3(3.f,3.f,3.f));
        m = m * m_scale;
        mvp = p*v*m;
        shader.setUniformMat4f("MVP",mvp);
        renderer.Draw(va,Orbite,shader);

        m = Orbite.getModelMatrix();
        m_scale = glm::scale(glm::mat4(1.f),glm::vec3(4.f,4.f,4.f));
        m = m * m_scale;
        mvp = p*v*m;
        shader.setUniformMat4f("MVP",mvp);
        renderer.Draw(va,Orbite,shader);

        m = Orbite.getModelMatrix();
        m_scale = glm::scale(glm::mat4(1.f),glm::vec3(5.f,5.f,5.f));
        m = m * m_scale;
        mvp = p*v*m;
        shader.setUniformMat4f("MVP",mvp);
        renderer.Draw(va,Orbite,shader);

        m = Orbite.getModelMatrix();
        m_scale = glm::scale(glm::mat4(1.f),glm::vec3(6.f,6.f,6.f));
        m = m * m_scale;
        mvp = p*v*m;
        shader.setUniformMat4f("MVP",mvp);
        renderer.Draw(va,Orbite,shader);

        m = Orbite.getModelMatrix();
        m_scale = glm::scale(glm::mat4(1.f),glm::vec3(7.f,7.f,7.f));
        m = m * m_scale;
        mvp = p*v*m;
        shader.setUniformMat4f("MVP",mvp);
        renderer.Draw(va,Orbite,shader);

        m = Orbite.getModelMatrix();
        m_scale = glm::scale(glm::mat4(1.f),glm::vec3(9.f,9.f,9.f));
        m = m * m_scale;
        mvp = p*v*m;
        shader.setUniformMat4f("MVP",mvp);
        renderer.Draw(va,Orbite,shader);

        m = Orbite.getModelMatrix();
        m_scale = glm::scale(glm::mat4(1.f),glm::vec3(10.f,10.f,10.f));
        m = m * m_scale;
        mvp = p*v*m;
        shader.setUniformMat4f("MVP",mvp);
        renderer.Draw(va,Orbite,shader);*/



        //Lune
        cam.computeMatrices(width, height);
        Lune.rotationAngles.y=PlanetSpeed;
        Lune.position = Terre.position+glm::vec3(20*cos(PlanetSpeed*2 + 1.7),0.f,15*sin(PlanetSpeed*2 + 1.7));
        m = Lune.getModelMatrix();
        m_scale = glm::scale(glm::mat4(1.f),glm::vec3(5.f,5.f,5.f));
        m = m * m_scale;
        v = cam.getViewMatrix();
        p = cam.getProjectionMatrix();
        mvp = p*v*m;
        shader.setUniformMat4f("MVP", mvp);
        shader.setUniformMat4f("m",m);
        renderer.Draw(va, Lune, shader);

        //Mars
        cam.computeMatrices(width, height);
        Mars.rotationAngles.y=PlanetSpeed;
        Mars.position = glm::vec3(500*cos(PlanetSpeed*0.35 + 1.7),0.f,500*sin(PlanetSpeed*0.35 + 1.7));
        m = Mars.getModelMatrix();
        m_scale = glm::scale(glm::mat4(1.f),glm::vec3(8.f,8.f,8.f));
        m = m * m_scale;
        v = cam.getViewMatrix();
        p = cam.getProjectionMatrix();
        mvp = p*v*m;
        shader.setUniformMat4f("MVP", mvp);
        shader.setUniformMat4f("m",m);
        renderer.Draw(va, Mars, shader);

        //Jupiter
        cam.computeMatrices(width, height);
        Jupiter.rotationAngles.y=PlanetSpeed*2.5;
        Jupiter.position = glm::vec3(600*cos(PlanetSpeed*0.2 + 5.12),0.f,600*sin(PlanetSpeed*0.2 + 5.12));
        m = Jupiter.getModelMatrix();
        m_scale = glm::scale(glm::mat4(1.f),glm::vec3(40.f,40.f,40.f));
        m = m * m_scale;
        v = cam.getViewMatrix();
        p = cam.getProjectionMatrix();
        mvp = p*v*m;
        shader.setUniformMat4f("MVP", mvp);
        shader.setUniformMat4f("m",m);
        renderer.Draw(va, Jupiter, shader);

        //Saturne
        cam.computeMatrices(width, height);
        Saturne.rotationAngles.y=PlanetSpeed*2.5;
        Saturne.position = glm::vec3(700*cos(PlanetSpeed*0.15 + 2.91),0.f,700*sin(PlanetSpeed*0.15 + 2.91));
        m = Saturne.getModelMatrix();
        m_scale = glm::scale(glm::mat4(1.f),glm::vec3(37.f,37.f,37.f));
        m = m * m_scale;
        v = cam.getViewMatrix();
        p = cam.getProjectionMatrix();
        mvp = p*v*m;
        shader.setUniformMat4f("MVP", mvp);
        shader.setUniformMat4f("m",m);
        renderer.Draw(va, Saturne, shader);
        //Anneau
        Anneau.position = Saturne.position;
        m = Anneau.getModelMatrix();
        m_scale = glm::scale(glm::mat4(1.f),glm::vec3(60.f,50.f,60.f));
        m = m * m_scale;
        v = cam.getViewMatrix();
        p = cam.getProjectionMatrix();
        mvp = p*v*m;
        shader.setUniformMat4f("MVP", mvp);
        shader.setUniformMat4f("m",m);
        renderer.Draw(va, Anneau, shader);

        //Uranus
        cam.computeMatrices(width, height);
        Uranus.rotationAngles.y=PlanetSpeed*1.4;
        Uranus.position = glm::vec3(900*cos(PlanetSpeed*0.1 + 3.97),0.f,900*sin(PlanetSpeed*0.1 + 3.97));
        m = Uranus.getModelMatrix();
        m_scale = glm::scale(glm::mat4(1.f),glm::vec3(30.f,30.f,30.f));
        m = m * m_scale;
        v = cam.getViewMatrix();
        p = cam.getProjectionMatrix();
        mvp = p*v*m;
        shader.setUniformMat4f("MVP", mvp);
        shader.setUniformMat4f("m",m);
        renderer.Draw(va, Uranus, shader);

        //Neptune
        cam.computeMatrices(width, height);
        Neptune.rotationAngles.y=PlanetSpeed*1.5;
        Neptune.position = glm::vec3(1000*cos(PlanetSpeed*0.08 + 0.35),0.f,1000*sin(PlanetSpeed*0.08 + 0.35));
        m = Neptune.getModelMatrix();
        m_scale = glm::scale(glm::mat4(1.f),glm::vec3(30.f,30.f,30.f));
        m = m * m_scale;
        v = cam.getViewMatrix();
        p = cam.getProjectionMatrix();
        mvp = p*v*m;
        shader.setUniformMat4f("MVP", mvp);
        shader.setUniformMat4f("m",m);
        renderer.Draw(va, Neptune, shader);

        //Skybox
        cam.computeMatrices(width,height);
        skybox.position = glm::vec3(0,0,0);
        m = skybox.getModelMatrix();
        m_scale = glm::scale(glm::mat4(1.f),glm::vec3(3000.f,3000.f,3000.f));
        m = m * m_scale;
        v = cam.getViewMatrix();
        p = cam.getProjectionMatrix();
        mvp = p*v*m;
        shader.setUniformMat4f("MVP",mvp);
        shader.setUniform1f("SunCoef",0);
        renderer.Draw(va,skybox,shader);

        //Soleil
        cam.computeMatrices(width, height);
        // On récupère la matrice modèle du Soleil
        m = Soleil.getModelMatrix();
        // On le place en (0,0,0)
        Soleil.position = glm::vec3(0.f,0.f,0.f);
        // On le multiplie par 100 dans toutes les dimensions
        m_scale = glm::scale(glm::mat4(1.f),glm::vec3(100.f,100.,100.f));
        //On calcule la matrice mvp
        m = m * m_scale;
        v = cam.getViewMatrix();
        p = cam.getProjectionMatrix();
        mvp = p*v*m;
        // On l'envoie au shader
        shader.setUniformMat4f("MVP", mvp);
        shader.setUniformMat4f("m",m);
        // On dessine le Soleil
        renderer.Draw(va, Soleil, shader);

        ////////////////Partie rafraichissement de l'image et des évènements///////////////
        //Swap buffers : frame refresh
        glfwSwapBuffers(window);
        //get the events
        glfwPollEvents();
    }
    glfwTerminate();




    return 0;
}
