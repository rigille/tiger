use std::sync::Arc;

pub enum Var {
    Simple {
        pos: Pos,
        sym: Symbol,
    },
    Field {
        pos: Pos,
        var: Arc<Var>,
        sym: Symbol,
    },
    Subscript {
        pos: Pos,
        var: Arc<Var>,
        exp: Exp,
    },
}
// TODO replace Vec with im::Vector
pub enum Exp {
    Var {
        pos: Pos,
        var: Arc<Var>,
    },
    Nil {
        pos: Pos,
    },
    Int {
        pos: Pos,
        i: i32,
    },
    Str {
        pos: Pos,
        s: String,
    },
    Call {
        pos: Pos,
        func: Symbol,
        args: Vec<Arc<Exp>>,
    },
    Op {
        pos: Pos,
        oper: Oper,
        left: Arc<Exp>,
        right: Arc<Exp>,
    },
    Record {
        pos: Pos,
        typ: Symbol,
        fields: Vec<Efield>,
    },
    Seq {
        pos: Pos,
        seq: Vec<Arc<Exp>>,
    },
    Assign {
        pos: Pos,
        var: Arc<Var>,
        exp: Arc<Exp>,
    },
    If {
        pos: Pos,
        test: Arc<Exp>,
        then: Arc<Exp>,
        elsee: Arc<Exp>,
    },
    While {
        pos: Pos,
        test: Arc<Exp>,
        body: Arc<Exp>,
    },
    For {
        pos: Pos,
        var: Symbol,
        lo: Arc<Exp>,
        hi: Arc<Exp>,
        body: Arc<Exp>,
    },
    Break {
        pos: Pos,
    },
    Let {
        pos: Pos,
        decs: Vec<Dec>,
        body: Arc<Exp>,
    },
    Array {
        pos: Pos,
        typ: Symbol,
        size: Arc<Exp>,
        init: Arc<Exp>,
    },
}
pub enum Dec {
    Function {
        pos: Pos,
        function: Vec<Arc<Fundec>>,
    },
    Var {
        pos: Pos,
        var: Symbol,
        typ: Symbol,
        init: Exp,
    },
    Type {
        pos: Pos,
        typ: Vec<NameTy>,
    },
}
pub enum Ty {
    Name { pos: Pos, name: Symbol },
    Record { pos: Pos, record: Vec<Field> },
    Array { pos: Pos, array: Symbol },
}
pub struct Field {
    pos: Pos,
    name: Symbol,
    typ: Symbol,
}
pub struct Fundec {
    pos: Pos,
    name: Symbol,
    params: Vec<Field>,
    result: Symbol,
}
pub struct NameTy {
    name: Symbol,
    ty: Ty,
}
pub struct Efield {
    name: Symbol,
    exp: Exp,
}
pub enum Oper {
    Plus,
    Minus,
    Times,
    Divide,
    Equals,
    Neq,
    Lt,
    Le,
    Gt,
    Ge,
}
type Symbol = String;
type Pos = (usize, usize);
