const PRODUCTS: [(&'static str, u16); 37] = [
    ("Product Flawnberry-5629", 0x5d2b),
    ("Product Flawnberry-3187", 0x4794),
    ("Product Flawnberry-3678", 0xc091),
    ("Product Flawnberry-4953", 0x640e),
    ("Product Flawnberry-4153", 0xde21),
    ("Product Flawnberry-7573", 0x548b),
    ("Product Flawnberry-5436", 0x7795),
    ("Product Flawnberry-5758", 0x25e6),
    ("Product Flawnberry-9495", 0x6b6e),
    ("Product Flawnberry-5002", 0xb742),
    ("Product Flawnberry-2731", 0xad46),
    ("Product Flawnberry-6701", 0x79b0),
    ("Product Flawnberry-8346", 0x88bb),
    ("Product Flawnberry-1315", 0x5c32),
    ("Product Flawnberry-9331", 0xc939),
    ("Product Flawnberry-8280", 0x73d2),
    ("Product Flawnberry-1179", 0xbd7c),
    ("Product Flawnberry-8942", 0x23bf),
    ("Product Flawnberry-8981", 0xdd36),
    ("Product Flawnberry-2810", 0xfa7a),
    ("Product Flawnberry-8880", 0xbea4),
    ("Product Flawnberry-4074", 0x8fb7),
    ("Product Flawnberry-1733", 0xdadd),
    ("Product Flawnberry-5748", 0xd290),
    ("Product Flawnberry-1233", 0xf569),
    ("Product Flawnberry-3638", 0xa3f0),
    ("Product Flawnberry-4639", 0x53e4),
    ("Product Flawnberry-7291", 0xcfd1),
    ("Product Flawnberry-4267", 0x24e1),
    ("Product Flawnberry-8307", 0xff10),
    ("Product Flawnberry-2361", 0x1d46),
    ("Product Flawnberry-6727", 0x34d6),
    ("Product Flawnberry-4286", 0x8626),
    ("Product Flawnberry-5212", 0xdfa2),
    ("Product Flawnberry-2850", 0x0854),
    ("Product Flawnberry-6239", 0x5a8d),
    ("Product Flawnberry-4872", 0xda79),
];

pub fn beautify(code: u16) -> Option<&'static str> {
    PRODUCTS.iter()
        .find(|&&(_, pid)| pid == code)
        .map(|&(name, _)| name)
}

pub fn beautify_manual(code: u16) -> Option<&'static str> {
    for product in PRODUCTS.iter() {
        if product.1 == code {
            return Some(product.0);
        }
    }
    None
}

pub fn beautify_copy(code: u16) -> Option<String> {
    PRODUCTS.iter().find_map(|&(name, pid)| if pid == code {
        Some(name.to_string())
    } else {
        None
    })
}

pub fn legal_codes() -> Vec<u16> {
    PRODUCTS.iter().map(|&(_, pid)| pid).collect()
}
