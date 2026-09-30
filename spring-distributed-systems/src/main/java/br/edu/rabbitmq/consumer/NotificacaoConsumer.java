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

/** Vinculado com pedido.* — recebe todos os eventos de pedido. */
@Component
public class NotificacaoConsumer {

    private static final Logger log = LoggerFactory.getLogger(NotificacaoConsumer.class);

    private final PedidoEventoValidator validator;

    public NotificacaoConsumer(PedidoEventoValidator validator) {
        this.validator = validator;
    }

    @RabbitListener(queues = RabbitMQConfig.FILA_NOTIFICACAO)
    public void processar(PedidoEvento evento,
                          @Header(AmqpHeaders.RECEIVED_ROUTING_KEY) String routingKey) {
        validator.validar(evento, routingKey);
        Pedido pedido = evento.pedido();

        String texto = switch (routingKey) {
            case RabbitMQConfig.RK_PEDIDO_CRIADO -> "recebemos seu pedido";
            case RabbitMQConfig.RK_PEDIDO_PAGO -> "pagamento confirmado";
            case RabbitMQConfig.RK_PEDIDO_CANCELADO -> "seu pedido foi cancelado";
            default -> "atualização no seu pedido";
        };
        log.info("[NOTIFICAÇÃO] Olá {}, {} (#{} - {})",
                pedido.cliente(), texto, pedido.id(), pedido.produto());
    }
}
