#include "Parser.h"

int main(int argc, char *argv[]){

    Vars var(var_types::tiv,"x", 5);
    Vars vars(var_types::tiv,"y", 8);
    Vars t(var);

    Tokenizer tk("code.txt");
    tk.tokenize_source_code();
    Parser ps;
    ps.parse(tk);
}

