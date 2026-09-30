package br.edu.rabbitmq.consumer;

import br.edu.rabbitmq.model.Pedido;
import br.edu.rabbitmq.model.PedidoEvento;
import br.edu.rabbitmq.model.StatusPedido;
import org.junit.jupiter.api.Test;
import org.springframework.amqp.AmqpRejectAndDontRequeueException;

import java.math.BigDecimal;
import java.time.Instant;

import static org.assertj.core.api.Assertions.assertThatCode;
import static org.assertj.core.api.Assertions.assertThatThrownBy;

class PedidoEventoValidatorTest {

    private final PedidoEventoValidator validator = new PedidoEventoValidator();

    private Pedido pedidoValido() {
        return new Pedido(1001L, "Maria", "Notebook", 2, new BigDecimal("3500"),
                StatusPedido.CRIADO, Instant.now());
    }

    @Test
    void aceitaEventoValido() {
        PedidoEvento evento = PedidoEvento.de("pedido.criado", pedidoValido());

        assertThatCode(() -> validator.validar(evento, "pedido.criado"))
                .doesNotThrowAnyException();
    }

    @Test
    void rejeitaEventoNulo() {
        assertThatThrownBy(() -> validator.validar(null, "pedido.criado"))
                .isInstanceOf(AmqpRejectAndDontRequeueException.class);
    }

    @Test
    void rejeitaTipoDiferenteDaRoutingKey() {
        PedidoEvento evento = PedidoEvento.de("pedido.pago", pedidoValido());

        assertThatThrownBy(() -> validator.validar(evento, "pedido.criado"))
                .isInstanceOf(AmqpRejectAndDontRequeueException.class)
                .hasMessageContaining("routing key");
    }

    @Test
    void rejeitaPedidoComCamposInvalidos() {
        Pedido invalido = new Pedido(1001L, " ", null, 0, new BigDecimal("-1"),
                StatusPedido.CRIADO, Instant.now());
        PedidoEvento evento = PedidoEvento.de("pedido.criado", invalido);

        assertThatThrownBy(() -> validator.validar(evento, "pedido.criado"))
                .isInstanceOf(AmqpRejectAndDontRequeueException.class)
                .hasMessageContaining("pedido.cliente")
                .hasMessageContaining("pedido.produto")
                .hasMessageContaining("pedido.quantidade")
                .hasMessageContaining("pedido.valor");
    }
}
