use std::fs::File;
use std::io::Read;

struct Vector2
{
    x: f32,
    y: f32
}
impl Vector2 
{
    fn new(x:f32, y: f32) -> Self 
    {
        Vector2
        {
            x:x,
            y:y
        }
    }
}

struct Vector3
{
    x: f32,
    y: f32,
    z: f32
}
impl Vector3
{
    fn new(x:f32, y: f32, z:f32) -> Self 
    {
        Vector3
        {
            x,
            y,
            z
        }
    }
}


fn main() 
{
    let mut buffer:[u8; 1] = [0; 1];
    let size = Vector3::new(10.0, 20.0, 30.0); 
    let mut matriz_3d: Vec<Vec<Vec<u8>>> = vec![vec![vec![0; size.x as usize]; size.y as usize]; size.z as usize];
    println!("Hello, world!");
}
