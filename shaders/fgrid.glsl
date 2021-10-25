#version 330

in vec3 position;
in mat4 viewMatrix;
in mat4 projMatrix;

out vec4 frag_color;

vec3 UnprojectPoint(float x, float y, float z, mat4 view, mat4 projection) {
    mat4 viewInv = inverse(view);
    mat4 projInv = inverse(projection);
    vec4 unprojectedPoint =  viewInv * projInv * vec4(x, y, z, 1.0);
    return unprojectedPoint.xyz / unprojectedPoint.w;
}

vec4 grid(vec3 fragPos3D, float scale) {
    vec2 coord = fragPos3D.xy * scale; // use the scale variable to set the distance between the lines
    vec2 derivative = fwidth(coord);
    vec2 grid = abs(fract(coord - 0.5) - 0.5) / derivative;
    float line = min(grid.x, grid.y);
    float minimumz = min(derivative.y, 1);
    float minimumx = min(derivative.x, 1);
    vec4 color = vec4(0.2, 0.2, 0.2, 1.0 - min(line, 1.0));
    // y axis
    if(fragPos3D.x > -10 * minimumx && fragPos3D.x < 10 * minimumx)
        color.y = 1.0;
    // x axis
    if(fragPos3D.y > -10 * minimumz && fragPos3D.y < 10 * minimumz)
        color.x = 1.0;
    return color;
}

float computeDepth(vec3 pos) {
    vec4 clip_space_pos = projMatrix * viewMatrix * vec4(pos.xyz, 1.0);
    return (clip_space_pos.z / clip_space_pos.w);
}

float computeLinearDepth(vec3 pos) {
    float near=0.1;
    float far=300.0;
    vec4 clip_space_pos = projMatrix * viewMatrix * vec4(pos.xyz, 1.0);
    float clip_space_depth = (clip_space_pos.z / clip_space_pos.w) * 2.0 - 1.0; // put back between -1 and 1
    float linearDepth = (2.0 * near * far) / (far + near - clip_space_depth * (far - near)); // get linear value between 0.01 and 100
    return linearDepth / far; // normalize
}

void main() {
    vec2 uv= (gl_FragCoord.xy/800.0)*2 -1;

      // unprojecting on the near plane
    vec3 nearPoint = UnprojectPoint(uv.x, uv.y, 0.0, viewMatrix, projMatrix).xyz;

    // unprojecting on the far plane
    vec3 farPoint = UnprojectPoint(uv.x, uv.y , 1.0, viewMatrix, projMatrix).xyz; 

    float t = -nearPoint.z / (farPoint.z - nearPoint.z);
    // opacity = 1 when t > 0, opacity = 0 otherwise
    //frag_color = vec4(1.0f, 0.0 , 0.0, 1.0*float(t > 0)); 

    vec3 fragPos3D = nearPoint + t * (farPoint - nearPoint);
    gl_FragDepth = computeDepth(fragPos3D);

    float linearDepth = computeLinearDepth(fragPos3D);
    float fading = max(0, (0.5 - linearDepth));

    frag_color = grid(fragPos3D, 0.1) * float(t > 0);
    frag_color.a *= fading;
    //frag_color = vec4(vec3(computeDepth(fragPos3D)),1.0);
}