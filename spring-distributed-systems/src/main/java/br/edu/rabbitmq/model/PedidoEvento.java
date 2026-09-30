package br.edu.rabbitmq.model;

import java.time.Instant;
import java.util.UUID;

/**
 * Envelope publicado na exchange TOPIC.
 * O {@code tipo} é o mesmo valor usado como routing key (ex.: pedido.criado).
 */
public record PedidoEvento(
        UUID eventoId,
        String tipo,
        Instant dataHora,
        Pedido pedido
) {

    public static PedidoEvento de(String tipo, Pedido pedido) {
        return new PedidoEvento(UUID.randomUUID(), tipo, Instant.now(), pedido);
    }
}
