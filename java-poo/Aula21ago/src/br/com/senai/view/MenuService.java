package br.com.senai.view;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class MenuService {

    private Scanner tec;
    private boolean exec = true;
    private List<MenuService> menuServiceList = new ArrayList<>();

    public void menu(){
        tec = new Scanner(System.in);
        do {
            System.out.println("1 - Cliente");
            System.out.println("2 - Endereco");
            System.out.println("3 - Funcionario");
            System.out.println("4 - Pessoa");
            System.out.println("9 - Encerrar o sistema");

            System.out.print("Informe a opção desejada: ");
            executarMetodo(tec.nextInt());

        }while(this.exec);
    }

    private void executarMetodo(int opcao){
        switch (opcao){

            case 1:
                //cliente
                break;

            case 2:
                //endereco
                break;

            case 3://funcionario]
                break;

            case 4:
                PessoaView pessoaView = new PessoaView();
                pessoaView.menu();
                break;

            case 9:
                this.exec = false;
                System.out.println("Sistema finalizado");
                break;

            default:
                System.out.println("Opção inválida!");
                break;

        }
    }


    /**
     * do {
     *                     System.out.println("1 - Adicionar");
     *                     System.out.println("2 - Listar");
     *                     System.out.println("3 - Buscar");
     *                     System.out.println("4 - Remover");
     *                     System.out.println("4 - Editar");
     *                     System.out.println("9 - Encerrar o sistema");
     *
     *                     System.out.print("Informe a opção desejada: ");
     *                     executarMetodo(tec.nextInt());
     *
     *                 }while(this.exec);
     *
     *                 String nomeCliente;
     *                 int id;
     *
     *                 System.out.println("Informe o nome do cliente: ");
     *                 tec.nextLine();
     *                 nomeCliente = tec.nextLine();
     *                 System.out.println("Informe o ID do cliente: ");
     *                 id = tec.nextDouble();
     *
     *                 Cliente cliente = clienteService.adicionarCliente(nomeCliente, id);
     *                 clientes.add(cliente);
     *
     *                 private void listarClientes(List<Cliente> cliente){
     *                 System.out.println("CLIENTES CADASTRADOS");
     *                 System.out.printf("%-10s | %-10s | %-10s \n", "CLIENTE", "ID");
     *
     *                 for (int i = 0; i < produtos.size(); i++){
     *                     System.out.printf("%-10s | %s%-10.2f | %-10d \n", clientes.get(i).getNomeCliente(), "ID", id.get(i).getId());
     *
     *                 }
     */
}
