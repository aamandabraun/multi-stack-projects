package br.edu.rabbitmq.consumer;

import br.edu.rabbitmq.model.Pedido;
import br.edu.rabbitmq.model.PedidoEvento;
import org.springframework.amqp.AmqpRejectAndDontRequeueException;
import org.springframework.stereotype.Component;

import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.List;

/**
 * O consumidor não confia no produtor: qualquer serviço pode publicar na exchange.
 * Mensagens com JSON válido mas conteúdo inconsistente são rejeitadas
 * (sem requeue) e seguem para a Dead Letter Queue.
 */
@Component
public class PedidoEventoValidator {

    public void validar(PedidoEvento evento, String routingKey) {
        List<String> erros = new ArrayList<>();

        if (evento == null) {
            throw new AmqpRejectAndDontRequeueException("Mensagem vazia");
        }
        if (evento.eventoId() == null) {
            erros.add("eventoId ausente");
        }
        if (evento.tipo() == null || !evento.tipo().equals(routingKey)) {
            erros.add("tipo '" + evento.tipo() + "' diferente da routing key '" + routingKey + "'");
        }

        Pedido pedido = evento.pedido();
        if (pedido == null) {
            erros.add("pedido ausente");
        } else {
            if (pedido.id() == null) erros.add("pedido.id ausente");
            if (isBlank(pedido.cliente())) erros.add("pedido.cliente ausente");
            if (isBlank(pedido.produto())) erros.add("pedido.produto ausente");
            if (pedido.quantidade() == null || pedido.quantidade() <= 0) erros.add("pedido.quantidade inválida");
            if (pedido.valor() == null || pedido.valor().compareTo(BigDecimal.ZERO) <= 0) erros.add("pedido.valor inválido");
            if (pedido.status() == null) erros.add("pedido.status ausente");
        }

        if (!erros.isEmpty()) {
            throw new AmqpRejectAndDontRequeueException("Mensagem inválida: " + String.join("; ", erros));
        }
    }

    private static boolean isBlank(String valor) {
        return valor == null || valor.isBlank();
    }
}
