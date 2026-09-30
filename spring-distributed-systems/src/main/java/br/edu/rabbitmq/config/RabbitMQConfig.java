package br.edu.rabbitmq.config;

import com.fasterxml.jackson.databind.ObjectMapper;
import org.springframework.amqp.core.Binding;
import org.springframework.amqp.core.BindingBuilder;
import org.springframework.amqp.core.Declarables;
import org.springframework.amqp.core.DirectExchange;
import org.springframework.amqp.core.Queue;
import org.springframework.amqp.core.QueueBuilder;
import org.springframework.amqp.core.TopicExchange;
import org.springframework.amqp.support.converter.Jackson2JsonMessageConverter;
import org.springframework.amqp.support.converter.MessageConverter;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

/**
 * Topologia do broker:
 *
 * <pre>
 *                        pedido.criado / pedido.pago / pedido.cancelado
 *   Producer ---------> [ pedidos.exchange (TOPIC) ]
 *                              |
 *        +---------------------+----------------------+
 *        | pedido.criado       | pedido.pago          | pedido.*
 *        | pedido.cancelado    | pedido.cancelado     |
 *        v                     v                      v
 *   estoque.queue        financeiro.queue      notificacao.queue
 *        \                     |                      /
 *         +---- rejeitadas ----+---- (dead letter) --+
 *                              v
 *              [ pedidos.dlx (DIRECT) ] --> pedidos.dlq
 * </pre>
 *
 * Além disso, a fila {@code mensagens.queue} (Etapas 1 e 2) recebe mensagens
 * pela default exchange, enviadas diretamente pelo nome da fila.
 */
@Configuration
public class RabbitMQConfig {

    // Etapas 1 e 2 — Hello RabbitMQ (default exchange, sem routing explícito)
    public static final String FILA_MENSAGENS = "mensagens.queue";

    // Etapas 4 e 5 — eventos de pedido
    public static final String EXCHANGE_PEDIDOS = "pedidos.exchange";

    public static final String FILA_ESTOQUE = "estoque.queue";
    public static final String FILA_FINANCEIRO = "financeiro.queue";
    public static final String FILA_NOTIFICACAO = "notificacao.queue";

    public static final String RK_PEDIDO_CRIADO = "pedido.criado";
    public static final String RK_PEDIDO_PAGO = "pedido.pago";
    public static final String RK_PEDIDO_CANCELADO = "pedido.cancelado";
    public static final String RK_TODOS_PEDIDOS = "pedido.*";

    // Tratamento de mensagens inválidas
    public static final String EXCHANGE_DLX = "pedidos.dlx";
    public static final String FILA_DLQ = "pedidos.dlq";
    public static final String RK_DLQ = "pedido.invalido";

    // ---------- Exchanges ----------

    @Bean
    public TopicExchange pedidosExchange() {
        return new TopicExchange(EXCHANGE_PEDIDOS, true, false);
    }

    @Bean
    public DirectExchange deadLetterExchange() {
        return new DirectExchange(EXCHANGE_DLX, true, false);
    }

    // ---------- Filas ----------

    @Bean
    public Queue filaMensagens() {
        return new Queue(FILA_MENSAGENS, true);
    }

    @Bean
    public Queue filaEstoque() {
        return filaComDeadLetter(FILA_ESTOQUE);
    }

    @Bean
    public Queue filaFinanceiro() {
        return filaComDeadLetter(FILA_FINANCEIRO);
    }

    @Bean
    public Queue filaNotificacao() {
        return filaComDeadLetter(FILA_NOTIFICACAO);
    }

    @Bean
    public Queue filaDlq() {
        return QueueBuilder.durable(FILA_DLQ).build();
    }

    /** Fila durável cujas mensagens rejeitadas são encaminhadas para a DLX. */
    private Queue filaComDeadLetter(String nome) {
        return QueueBuilder.durable(nome)
                .deadLetterExchange(EXCHANGE_DLX)
                .deadLetterRoutingKey(RK_DLQ)
                .build();
    }

    // ---------- Bindings ----------

    @Bean
    public Declarables bindingsPedidos(TopicExchange pedidosExchange,
                                       Queue filaEstoque,
                                       Queue filaFinanceiro,
                                       Queue filaNotificacao) {
        return new Declarables(
                // Estoque: reserva ao criar, devolve ao cancelar
                BindingBuilder.bind(filaEstoque).to(pedidosExchange).with(RK_PEDIDO_CRIADO),
                BindingBuilder.bind(filaEstoque).to(pedidosExchange).with(RK_PEDIDO_CANCELADO),

                // Financeiro: confirma pagamento, estorna ao cancelar
                BindingBuilder.bind(filaFinanceiro).to(pedidosExchange).with(RK_PEDIDO_PAGO),
                BindingBuilder.bind(filaFinanceiro).to(pedidosExchange).with(RK_PEDIDO_CANCELADO),

                // Notificação: interessada em todos os eventos de pedido
                BindingBuilder.bind(filaNotificacao).to(pedidosExchange).with(RK_TODOS_PEDIDOS)
        );
    }

    @Bean
    public Binding bindingDlq(DirectExchange deadLetterExchange, Queue filaDlq) {
        return BindingBuilder.bind(filaDlq).to(deadLetterExchange).with(RK_DLQ);
    }

    // ---------- Serialização ----------

    /**
     * Publica e consome objetos Java como JSON (Etapa 3).
     * Reaproveita o ObjectMapper do Spring Boot (suporte a datas java.time).
     */
    @Bean
    public MessageConverter jsonMessageConverter(ObjectMapper objectMapper) {
        return new Jackson2JsonMessageConverter(objectMapper);
    }
}
