package br.com.senai.view;

import br.com.senai.entity.Pessoa;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class PessoaView {
    private Scanner tec;
    private boolean exec = true;
    private List<Pessoa> pessoas = new ArrayList<>();

    public void menu(){
        tec = new Scanner(System.in);
        do {
            System.out.println("1 - Adicionar");
            System.out.println("2 - Listar");
            System.out.println("3 - Buscar");
            System.out.println("4 - Remover");
            System.out.println("4 - Editar");
            System.out.println("9 - Retornar ao menu principal");

            System.out.print("Informe a opção desejada: ");
            executarMetodo(tec.nextInt());

        }while(this.exec);
    }

    private void executarMetodo(int opcao){
        switch (opcao){

            case 1:
                //adicionar
                 break;

            case 2:
                //listar
                break;

            case 3:
                //buscar
                break;

            case 4:
                //remover
                break;

            case 5:
                //editar
                break;

            case 9:
                this.exec = false;
                System.out.println("Saindo de PESSOA");
                break;

            default:
                System.out.println("Opção inválida!");
                break;

        }

    }
}
