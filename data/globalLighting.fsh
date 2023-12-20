//material properties
uniform sampler2D u_texture1;
uniform sampler2D u_specMap;

//diffuse properties
uniform vec3 u_sunDirection;
const vec3 SUN_COLOR = vec3(1,1,1);

//scene properties
uniform vec3 u_ambientLight;
uniform vec3 u_viewPos;

//specular properties
//spec light comes from sun so can just reuse that
uniform float shininess;

//varyings
in vec2 v_uv1;
in vec4 v_normal;
in vec3 v_pos;
in vec4 v_tangent;
out vec4 PixelColor;

void main()
{
    vec3 diffuseMat = texture(u_texture1, v_uv1).rgb;

#ifdef ENABLE_DIFFUSE_AMBIENT
    vec3 normal = normalize(v_normal.xyz);
    vec3 diffuseLight = SUN_COLOR * max(0.0, dot(normal, u_sunDirection));//diffuse
    vec3 diffuseColor = diffuseMat * (diffuseLight + u_ambientLight);

#ifdef ENABLE_SPECULAR //diffues/ambient/specular
    vec3 pxToCam = normalize(u_viewPos - v_pos);
    vec3 spec;

#ifdef SPECULAR_MAP
    float specSample = texture(u_specMap, v_uv1).r;
    spec = SUN_COLOR * pow(max(0.0, dot(reflect(-u_sunDirection, normal), pxToCam)), shininess * pow(specSample,5)) * pow(specSample,1.5);
#else//no specular map for road
    float downTone = 0.1;
    spec = SUN_COLOR * (pow(max(0.0, dot(reflect(-u_sunDirection, normal), pxToCam)), shininess)/3);
#endif

    PixelColor.rgb = diffuseColor + spec;

#else // diffuse/ambient but no specular
    PixelColor.rgb = diffuseColor;
#endif//ENABLE_SPECULAR end

#else //no lighting
    PixelColor = diffuseMat;
#endif
    PixelColor.a = 1.0;

}


