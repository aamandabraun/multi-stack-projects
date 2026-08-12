package biblioteca;

class Livro {
    private String titulo;
    private String autor;
    private String isbn;
    private int ano;
    private boolean emprestado;

    public Livro (String titulo, String autor, String isbn, int ano, boolean emprestado){
        this.titulo = titulo;
        this.autor = autor;
        this.isbn = isbn;
        this.ano = ano;
        this.emprestado = false;
    }

    public String getTitulo() {
        return titulo;
    }public void setTitulo(String titulo) {
        this.titulo = titulo;
    }

    public String getAutor() {
        return autor;
    }public void setAutor(String autor) {
        this.autor = autor;
    }

    public String getIsbn() {
        return isbn;
    }public void setIsbn(String isbn) {
        this.isbn = isbn;
    }

    public int getAno() {
        return ano;
    }public void setAno(int ano) {
        this.ano = ano;
    }

    public boolean isEmprestado(){
        return emprestado;
    }

    public void emprestar(){
        this.emprestado = true;
    }

    public void devolver(){
        this.emprestado = false;
    }

    @Override
    public String toString(){
        return titulo + " - " + autor + " ( " + ano + " ) | ISBN: " + isbn + " | " + (emprestado ? "Indisponível" : "Disponível");
    }
}
