// Designed by Misfit beam project
// Ref to Arduino nano size, 0.73" x 1.70" 
// https://www.arduino.cc/en/Main/arduinoBoardNano
// Length	45 mm
// Width	18 mm
length = 90;
width = 50;
height = 20;
thick = 3;
neck = 1;

// docker
// real size 27.5 mm * 67.5 mm
// hole r 1 mm
// hole_offset_x = 1 mm
docker_hole_size = 2;
docker_hole_height = 3;
docker_offset_x = 1;
docker_offset_y = 1;
docker_x = 67.5;
docker_y = 27.5; 

// IR LED
led_r = 3;

// switch size
switch_length = 19.3;
switch_width = 9.5;

module cover(length, width, thick){
    cube(size = [length, width, thick]);
}

module coverWithLogo(length, width, thick){
    cube(size = [length, width, thick]);
    
    translate([length / 2 - 9, width / 2 - 7 ,thick])
    resize([20,0,0.1], auto=true)
    surface(file = "misfit.png", invert = false);
}

module box(){    
    cube(size = [length,width, thick]);
    
    x_offset = (length - docker_x) / 2 - docker_hole_size / 2;
    y_offset = (width - docker_y) / 2 - docker_hole_size / 2;
    
    z_offset = thick;
    
    translate([x_offset, y_offset, z_offset])
    cylinder(h = docker_hole_height, r1=docker_hole_size, r2=docker_hole_size/3,$fs=6);

    translate([length - x_offset, y_offset, z_offset])
    cylinder(h = docker_hole_height, r1=docker_hole_size, r2=docker_hole_size/3,$fs=6);
  
    translate([x_offset, width - y_offset, z_offset])
    cylinder(h = docker_hole_height, r1=docker_hole_size, r2=docker_hole_size/3,$fs=6);
  
    translate([length - x_offset, width - y_offset, z_offset])
    cylinder(h = docker_hole_height, r1=docker_hole_size, r2=docker_hole_size/3,$fs=6);

    translate([length - thick,0,0])
    cube(size = [thick, width, height - neck * 2]);
    
    translate([0,0,0])
    cube(size = [thick, width, height]);

    translate([0,0,0])
    cube(size = [length, thick, height]);

    translate([0,width,0])
    cube(size = [length, thick, height]);
    
    translate([length / 2 - 20, width / 2 - 7, -3])
    cube(size = [40, 14, thick]);
}

module hole(pos){
    translate([pos, width - thick, height / 2])
    rotate([90,0,0])
    cylinder(h = 20, r = led_r, center = true);
}

module switch(x){
    translate([length - thick, x, 5])
    cube(size = [5, switch_length, switch_width]);
} 

// Main box
module mainbox() {
    // Main box
    difference() {
        difference() {
            box();
            
            translate([neck, neck, height - neck * 2])
            cover(length, width, neck);       
        }
        hole(10);
        hole(25);
        hole(40);
        switch(width - switch_length - 5);
    }
}


// Main box...
mainbox();

// Cover
neck_detla = 0.3;
translate([0, 0, 30])
coverWithLogo(length - neck - neck_detla, width - neck - neck_detla, neck - neck_detla);