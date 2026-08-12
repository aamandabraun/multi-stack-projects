package br.com.senai;

import br.com.senai.entity.Funcionario;
import br.com.senai.service.FuncionarioService;
import br.com.senai.view.ProductView;

public class Application {

    //public static void main(String[] args){
    //    ProductView view = new ProductView();
    //    view.menu();

    public static void main(String[] args) {
        FuncionarioService funcionarioService = new FuncionarioService();
        funcionarioService.cadastrarFuncionario();
    }

}
