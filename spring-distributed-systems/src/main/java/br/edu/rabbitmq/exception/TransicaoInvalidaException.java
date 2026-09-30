package br.edu.rabbitmq.exception;

import br.edu.rabbitmq.model.StatusPedido;

public class TransicaoInvalidaException extends RuntimeException {

    public TransicaoInvalidaException(Long id, StatusPedido atual, StatusPedido destino) {
        super("Pedido " + id + " está " + atual + " e não pode passar para " + destino);
    }
}
