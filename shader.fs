/* Fragment shader file */

#version 330 core
    // input parameters
    in vec2 TexCoord;
    in vec3 FragPos;
    in vec3 Normal;

   // texture
   uniform sampler2D texture1;
   uniform vec3 lightColor;
   uniform vec3 lightPos;
   uniform vec3 viewPos;

    // output parameters
    // here: gets color from vertex shader
    out vec4 FragColor;

    void main()
    {
      vec4 textColor = texture(texture1, TexCoord);

      // ambient color
      float ambientStrength = 0.1;
      vec3 ambientColor = (ambientStrength * lightColor) * textColor.xyz;

      // diffuse color
      vec3 norm = normalize(Normal);
      vec3 lightDir = normalize(lightPos - FragPos);
      vec3 diffuseColor = max(dot(norm, lightDir), 0.0) * lightColor * textColor.xyz;


      // specular color
      float specularStrength = 0.5;
      vec3 viewDir = normalize(viewPos - FragPos);
      vec3 reflectDir = reflect(-lightDir, norm);
      vec3 specularColor = pow(max(dot(viewDir, reflectDir), 0.0), 32) * specularStrength * textColor.xyz;

      FragColor = vec4(ambientColor + diffuseColor + specularColor, textColor.w);
    }