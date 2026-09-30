package br.edu.rabbitmq.consumer;

import br.edu.rabbitmq.config.RabbitMQConfig;
import br.edu.rabbitmq.model.Pedido;
import br.edu.rabbitmq.model.PedidoEvento;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.amqp.rabbit.annotation.RabbitListener;
import org.springframework.amqp.support.AmqpHeaders;
import org.springframework.messaging.handler.annotation.Header;
import org.springframework.stereotype.Component;

/** Consome financeiro.queue: pedido.pago (registro) e pedido.cancelado (estorno). */
@Component
public class PagamentoConsumer {

    private static final Logger log = LoggerFactory.getLogger(PagamentoConsumer.class);

    private final PedidoEventoValidator validator;

    public PagamentoConsumer(PedidoEventoValidator validator) {
        this.validator = validator;
    }

    @RabbitListener(queues = RabbitMQConfig.FILA_FINANCEIRO)
    public void processar(PedidoEvento evento,
                          @Header(AmqpHeaders.RECEIVED_ROUTING_KEY) String routingKey) {
        validator.validar(evento, routingKey);
        Pedido pedido = evento.pedido();

        switch (routingKey) {
            case RabbitMQConfig.RK_PEDIDO_PAGO -> log.info(
                    "[PAGAMENTO] Pagamento de R$ {} registrado para o pedido {} ({})",
                    pedido.valor(), pedido.id(), pedido.cliente());
            case RabbitMQConfig.RK_PEDIDO_CANCELADO -> log.info(
                    "[PAGAMENTO] Pedido {} cancelado — nenhuma cobrança será efetuada",
                    pedido.id());
            default -> log.warn("[PAGAMENTO] Evento {} ignorado", routingKey);
        }
    }
}
