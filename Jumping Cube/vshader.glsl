attribute  vec4 vPosition;
attribute  vec4 vColor;
varying vec4 color;
attribute   vec3 vNormal;


uniform mat4 ModelView;
uniform mat4 Projection;

varying  vec3 fN;


void main(){
    
    
    fN = vNormal;
    
    
    gl_Position = Projection * ModelView * vPosition;
    color = vColor;
    
}
