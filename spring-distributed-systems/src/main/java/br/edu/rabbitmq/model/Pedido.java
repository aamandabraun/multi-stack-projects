package br.edu.rabbitmq.model;

import java.math.BigDecimal;
import java.time.Instant;

/** Pedido da Etapa 3: id, cliente, produto, quantidade e valor, publicado como JSON. */
public record Pedido(
        Long id,
        String cliente,
        String produto,
        Integer quantidade,
        BigDecimal valor,
        StatusPedido status,
        Instant criadoEm
) {

    public Pedido comStatus(StatusPedido novoStatus) {
        return new Pedido(id, cliente, produto, quantidade, valor, novoStatus, criadoEm);
    }
}
