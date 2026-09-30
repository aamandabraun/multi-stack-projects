package br.edu.rabbitmq.controller;

import br.edu.rabbitmq.config.RabbitMQConfig;
import org.springframework.amqp.core.Message;
import org.springframework.amqp.core.MessageBuilder;
import org.springframework.amqp.core.MessageProperties;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.nio.charset.StandardCharsets;
import java.util.Map;
import java.util.Set;

/**
 * Apenas para demonstração em aula: publica um payload arbitrário (sem validação)
 * na exchange, simulando um produtor defeituoso. Útil para ver a mensagem
 * inválida ser rejeitada e parar na pedidos.dlq.
 */
@RestController
@RequestMapping("/testes")
public class TesteController {

    private static final Set<String> ROUTING_KEYS_PERMITIDAS = Set.of(
            RabbitMQConfig.RK_PEDIDO_CRIADO,
            RabbitMQConfig.RK_PEDIDO_PAGO,
            RabbitMQConfig.RK_PEDIDO_CANCELADO
    );

    private final RabbitTemplate rabbitTemplate;

    public TesteController(RabbitTemplate rabbitTemplate) {
        this.rabbitTemplate = rabbitTemplate;
    }

    @PostMapping("/mensagem-invalida")
    public ResponseEntity<Map<String, String>> publicarInvalida(
            @RequestParam(defaultValue = RabbitMQConfig.RK_PEDIDO_CRIADO) String routingKey,
            @RequestBody String payload) {

        if (!ROUTING_KEYS_PERMITIDAS.contains(routingKey)) {
            return ResponseEntity.badRequest()
                    .body(Map.of("erro", "routingKey deve ser uma de " + ROUTING_KEYS_PERMITIDAS));
        }

        Message message = MessageBuilder
                .withBody(payload.getBytes(StandardCharsets.UTF_8))
                .setContentType(MessageProperties.CONTENT_TYPE_JSON)
                .build();
        rabbitTemplate.send(RabbitMQConfig.EXCHANGE_PEDIDOS, routingKey, message);

        return ResponseEntity.accepted()
                .body(Map.of("status", "Payload publicado em " + routingKey + " — acompanhe a pedidos.dlq"));
    }
}
