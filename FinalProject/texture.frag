#version 130

//
// Texture mapping vertex shader
//
// Contributor:  YOUR_NAME_HERE
//

// INCOMING DATA
uniform sampler2D texture1;

// ADD VARIABLES HERE for all data being sent from your vertex shader
in vec2 texCoord;

// OUTGOING DATA

out vec4 finalColor;

///
// Main function
///

void main()
{
      // REPLACE THIS CODE with your implementation of this shader
	

  
	finalColor = texture(texture1,texCoord);
	
}
