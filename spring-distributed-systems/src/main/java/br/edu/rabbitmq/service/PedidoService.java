package br.edu.rabbitmq.service;

import br.edu.rabbitmq.config.RabbitMQConfig;
import br.edu.rabbitmq.dto.PedidoRequest;
import br.edu.rabbitmq.exception.PedidoNaoEncontradoException;
import br.edu.rabbitmq.exception.TransicaoInvalidaException;
import br.edu.rabbitmq.model.Pedido;
import br.edu.rabbitmq.model.PedidoEvento;
import br.edu.rabbitmq.model.StatusPedido;
import br.edu.rabbitmq.producer.PedidoProducer;
import br.edu.rabbitmq.repository.PedidoRepository;
import org.springframework.stereotype.Service;

import java.time.Instant;
import java.util.List;

@Service
public class PedidoService {

    private final PedidoRepository repository;
    private final PedidoProducer producer;

    public PedidoService(PedidoRepository repository, PedidoProducer producer) {
        this.repository = repository;
        this.producer = producer;
    }

    public Pedido criar(PedidoRequest request) {
        Pedido pedido = new Pedido(
                repository.proximoId(),
                request.cliente().trim(),
                request.produto().trim(),
                request.quantidade(),
                request.valor(),
                StatusPedido.CRIADO,
                Instant.now()
        );
        // Publica antes de salvar: se o broker falhar, o pedido não fica "órfão" sem evento
        producer.publicar(PedidoEvento.de(RabbitMQConfig.RK_PEDIDO_CRIADO, pedido));
        return repository.salvar(pedido);
    }

    public Pedido pagar(Long id) {
        return transicionar(id, StatusPedido.PAGO, RabbitMQConfig.RK_PEDIDO_PAGO);
    }

    public Pedido cancelar(Long id) {
        return transicionar(id, StatusPedido.CANCELADO, RabbitMQConfig.RK_PEDIDO_CANCELADO);
    }

    public Pedido buscar(Long id) {
        return repository.buscarPorId(id)
                .orElseThrow(() -> new PedidoNaoEncontradoException(id));
    }

    public List<Pedido> listar() {
        return repository.listar();
    }

    /** Só pedidos CRIADO podem ser pagos ou cancelados. */
    private Pedido transicionar(Long id, StatusPedido destino, String routingKey) {
        Pedido atual = buscar(id);
        if (atual.status() != StatusPedido.CRIADO) {
            throw new TransicaoInvalidaException(id, atual.status(), destino);
        }
        Pedido atualizado = atual.comStatus(destino);
        producer.publicar(PedidoEvento.de(routingKey, atualizado));
        return repository.salvar(atualizado);
    }
}
