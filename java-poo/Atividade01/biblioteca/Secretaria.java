package biblioteca;

import java.util.ArrayList;
import java.util.List;

public class Secretaria {
    private List<Livro> livros = new ArrayList<>();

    public void cadastrarLivro(String titulo, String autor, String isbn, int ano){
        livros.add(new Livro(titulo, autor, isbn, ano));
        System.out.println("Livro cadastrado");
    }

    public void emprestarLivro(String isbn){
        for (Livro livro : livros){
            if (livro.getIsbn().equals(isbn)){
                if (!livro.isEmprestado()){
                    livro.emprestar();
                    System.out.println("Livro emprestado");
                } else {
                    System.out.println("Livro indisponível");
                }
                return;
            }
        }
        System.out.println("Livro não encontrado");
    }

    public void devolverLivro(String isbn){
        for (Livro livro : livros){
            if (livro.getIsbn().equals(isbn)){
                System.out.println(livro);
                return;
            }
        }
        System.out.println("Livro não encontrado");
    }

    public void listarLivrosPorAutor(String autor){
        boolean encontrado = false;
        for (Livro livro = livros){
            if (livro.getAutor().equalsIgnoreCase(autor)){
                System.out.println(livro);
                encontrado = true;
            }
        }
        if (!encontrado) {
            System.out.println("Não temos livro deste autor");
        }
    }

    public void listarTodos(){
        if (livros.isEmpty()){
            System.out.println("Nenhum livro cadastrado");
            return;
        }
        for (Livro livro : livros){
            System.out.println(livro);
        }
    }
}
