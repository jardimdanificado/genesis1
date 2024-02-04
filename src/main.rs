use std::fs::File;
use std::io::{self, Read};
use std::collections::HashMap;


fn readtxt(caminho: &str) -> io::Result<String> {
    let mut conteudo = String::new();
    let mut arquivo = File::open(caminho)?;

    arquivo.read_to_string(&mut conteudo)?;
    
    Ok(conteudo)
}

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

fn atoi(s: &str) -> Option<i32> {
    // Remove espaços em branco do início e do final da string
    let s = s.trim();

    // Verifica se a string está vazia
    if s.is_empty() {
        return None;
    }

    // Inicializa o resultado como zero
    let mut result = 0;

    // Inicializa o sinal como positivo por padrão
    let mut sign = 1;

    // Se o primeiro caractere for um sinal, atualiza o sinal e avança para o próximo caractere
    let mut chars = s.chars();
    if let Some(first_char) = chars.next() {
        match first_char {
            '-' => sign = -1,
            '+' => (),
            _ => {
                // Se o primeiro caractere não for um sinal, volta um caractere
                result = match first_char.to_digit(10) {
                    Some(digit) => digit as i32,
                    None => return None, // Caractere inválido
                };
            }
        }
    }

    // Processa os caracteres restantes
    for c in chars {
        match c.to_digit(10) {
            Some(digit) => {
                // Atualiza o resultado multiplicando por 10 e somando o dígito
                result = result.checked_mul(10)?.checked_add(digit as i32)?;
            }
            None => return None, // Caractere inválido
        }
    }

    // Multiplica o resultado pelo sinal
    Some(result * sign)
}

fn parseini(text:String) -> HashMap<String, HashMap<String, String>>
{
    let lines = text.lines();
    let mut section = "all";
    let mut key = "";
    let mut value = "";
    let mut sectionlist: HashMap<String, HashMap<String, String>> = HashMap::new();
    //let mut inilist = HashMap::new();
    sectionlist.insert(String::from("all"), HashMap::new());
    for line in lines
    {
        if line.starts_with("[") && line.ends_with("]")
        {
            section = line;
            section = section.trim_start_matches('[');
            section = section.trim_end_matches(']');
            let mut _list: HashMap<String, String> = HashMap::new();
            sectionlist.insert(String::from(section), _list);
        }
        else
        {
            let mut parts = line.split("=");
            key = parts.next().unwrap();//unwrap retorna o valor do Option
            value = parts.next().unwrap();//unwrap retorna o valor do Option
            key = key.trim();//remove os espaços em branco
            value = value.trim();//remove os espaços em branco
            match sectionlist.get_mut(section)
            {
                Some(sec) => 
                {
                    sec.insert(String::from(key), String::from(value));
                }
                None => println!("Erro ao inserir a chave e o valor na seção")
            }
                
        }
    }
    return sectionlist;
}

struct Ini 
{
    data: HashMap<String, HashMap<String, String>>
}
impl Ini
{
    fn new(data: HashMap<String, HashMap<String, String>>) -> Self
    {
        Ini
        {
            data
        }
    }
    fn from_file(file: &str) -> Self
    {
        let text = readtxt(file).unwrap();
        let data = parseini(text);
        Ini
        {
            data
        }
    }
    fn get(&self, section: &str, key: &str) -> &String
    {
        let sec = self.data.get(section);
        let result = sec.unwrap().get(key).unwrap();
        return result;
    }
}

fn main()
{
    let ini = Ini::from_file("config.ini");
    println!("resultado = {}",ini.get("all", "nome"));
    let size = Vector3::new(10.0, 20.0, 30.0); 
    let matriz_3d: Vec<Vec<Vec<u8>>> = vec![vec![vec![0; size.x as usize]; size.y as usize]; size.z as usize];
    //println!("Hello, world!");
}
