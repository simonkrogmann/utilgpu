const float bias = 0.00001;

float shadowmapLookup(sampler2D shadowmap, mat4 lightViewProjection, vec3 worldPosition, vec3 normal) {
    vec4 lightPos = lightViewProjection * vec4(worldPosition, 1.0);
    lightPos /= lightPos.w;
    lightPos = lightPos * 0.5 + 0.5;
    return step(lightPos.z, texture(shadowmap, lightPos.xy).r + bias);
}
