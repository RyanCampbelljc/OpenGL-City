uniform mat4 u_mWVP;
uniform mat4 u_worldIT;
uniform mat4 u_world;

in vec4 a_position;
in vec2 a_uv1;
in vec3 a_normal;
in vec3 a_tangent;

out vec2 v_uv1;
out vec4 v_normal;
out vec3 v_pos;
out vec4 v_tangent;

void main()
{
    gl_Position = u_mWVP * a_position;
    v_pos =  (u_world * a_position).xyz;
    v_uv1 = a_uv1;
    v_normal = u_worldIT * vec4(a_normal, 0.0);
    v_tangent = u_worldIT * vec4(a_tangent, 0.0);
}
