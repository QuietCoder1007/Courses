/******************************************/
/*!!!!!DO NOT MODIFY PAST THIS POINT!!!!!!*/
/******************************************/
void build_table() {
    vector<vec4> mesh_vertices;
    vector<vec2> mesh_uvCoords;
    vector<vec3> mesh_normals;
    // Bind sphere vertex array object
    glBindVertexArray(VAOs[Cube]);

    // Load sphere model and store number of vertices
    loadOBJ(models[Cube], mesh_vertices, mesh_uvCoords, mesh_normals);
    numVertices[Cube] = mesh_vertices.size();

    // Bind sphere positions
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[CubePosBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*meshPosCoords*numVertices[Cube], mesh_vertices.data(), GL_STATIC_DRAW);

    // Bind pyramid vertex array object
    glBindVertexArray(VAOs[Target]);

    // Define vertices
    GLfloat vertices[68][3] = {
            {-TABLE_SIZE/3, 0.02f, 0.0f},
            {TABLE_SIZE/3, 0.02f, 0.0f},
            {0.0f, 0.02f, TABLE_SIZE/3},
            {0.0f, 0.02f,-TABLE_SIZE/3}
    };

    for (int i = 4; i < 68; i++) {
        vertices[i][0] = CIRCLE_RAD*sin((i-4)*0.1f);
        vertices[i][1] = 0.02f;
        vertices[i][2] = CIRCLE_RAD*cos((i-4)*0.1f);
    }

    // Define target colors (per vertex)
    GLfloat colors[68][4] = {
            {0.0f, 0.0f, 0.0f, 1.0f},
            {0.0f, 0.0f, 0.0f, 1.0f},
            {0.0f, 0.0f, 0.0f, 1.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
    };
    for (int i = 4; i < 68; i++) {
        colors[i][0] = 0.0f;
        colors[i][1] = 0.0f;
        colors[i][2] = 0.0f;
        colors[i][3] = 1.0f;
    }
    // Bind target positions
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[TargPosBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind target colors
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[TargColBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
}

void draw_table(){
    mat4 scale_matrix = scale(TABLE_SIZE, 0.01f, TABLE_SIZE);
    mat4 trans_matrix = translate(0.0f, -0.2f, 0.0f);
    model_matrix = scale_matrix;
    draw_obj(VAOs[Cube], Buffers[CubePosBuffer], numVertices[Cube], table_color);

    if (mode < 3) {
        model_matrix = mat4().identity();
    } else {
        mat4 targ_trans = translate(TARGET_X, TARGET_Y, TARGET_Z);
        model_matrix = targ_trans;
    }
    draw_target();
}
void draw_obj(GLuint VAO, GLuint Buffer, int numVert, vec4 color) {
    // TODO: Select mesh shader program
    glUseProgram(mesh_program);

    // TODO: Pass projection, camera, and model matrix to mesh shader
    glUniformMatrix4fv(mesh_proj_mat_loc, 1, GL_FALSE, proj_matrix);
    glUniformMatrix4fv(mesh_cam_mat_loc, 1, GL_FALSE, camera_matrix);
    glUniformMatrix4fv(mesh_model_mat_loc, 1, GL_FALSE, model_matrix);

    // TODO: Pass sphere color to mesh shader
    glUniform4fv(mesh_vCol, 1, color);
    // Bind vertex array object and vertex buffer
    glBindVertexArray(VAO);
    // TODO: Bind attribute buffers and set mesh vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, Buffer);
    glVertexAttribPointer(mesh_vPos, meshPosCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(mesh_vPos);

    // Draw mesh
    glDrawArrays(GL_TRIANGLES, 0, numVert);
}

void draw_target(){
    // TODO: Select gradient shader program
    glUseProgram(grad_program);

    // Bind Cube vertex array object
    glBindVertexArray(VAOs[Target]);
    // TODO: Bind attribute buffers and set gradient vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[TargPosBuffer]);
    glVertexAttribPointer(grad_vPos, pyrPosCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(grad_vPos);

    glBindBuffer(GL_ARRAY_BUFFER, Buffers[TargColBuffer]);
    glVertexAttribPointer(grad_vCol, pyrColCoords, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(grad_vCol);

    // TODO: Pass projection, camera, and model matrix to grad shader
    glUniformMatrix4fv(grad_proj_mat_loc, 1, GL_FALSE, proj_matrix);
    glUniformMatrix4fv(grad_cam_mat_loc, 1, GL_FALSE, camera_matrix);
    glUniformMatrix4fv(grad_model_mat_loc, 1, GL_FALSE, model_matrix);
    // Draw target
    glDrawArrays(GL_LINES, 0, 4);
    if (mode > 2) {
        glDrawArrays(GL_LINE_LOOP, 4, 64);
    }

}


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Esc closes window
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, true);
    }

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        mode++;
        if (mode == 3) {
            spin_flag = true;
        } else if (mode == 6) {
            rev_flag = true;
        } else if (mode > NUM_MODES)
        {
            mode = 0;
            spin_theta = 0.0f;
            rev_theta = 0.0f;
            spin_flag = true;
            rev_flag = true;
        }

    }

    // Adjust azimuth
    if (key == GLFW_KEY_A) {
        azimuth += daz;
        if (azimuth > 360.0) {
            azimuth -= 360.0;
        }
    } else if (key == GLFW_KEY_D) {
        azimuth -= daz;
        if (azimuth < 0.0)
        {
            azimuth += 360.0;
        }
    }

    // Adjust elevation angle
    if (key == GLFW_KEY_W)
    {
        elevation += del;
        if (elevation > 180.0)
        {
            elevation = 179.0;
        }
    }
    else if (key == GLFW_KEY_S)
    {
        elevation -= del;
        if (elevation < 0.0)
        {
            elevation = 1.0;
        }
    }

    // Compute updated camera position
    GLfloat x, y, z;
    x = (GLfloat)(radius*sin(azimuth*DEG2RAD)*sin(elevation*DEG2RAD));
    y = (GLfloat)(radius*cos(elevation*DEG2RAD));
    z = (GLfloat)(radius*cos(azimuth*DEG2RAD)*sin(elevation*DEG2RAD));
    eye = vec3(x,y,z);
}

void mouse_callback(GLFWwindow *window, int button, int action, int mods){

}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // TODO: Store new window sizes in global variables
    ww = width;
    hh = height;
}

