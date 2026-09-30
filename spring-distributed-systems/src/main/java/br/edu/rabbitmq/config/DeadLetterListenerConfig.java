package br.edu.rabbitmq.config;

import org.springframework.amqp.rabbit.config.SimpleRabbitListenerContainerFactory;
import org.springframework.amqp.rabbit.connection.ConnectionFactory;
import org.springframework.amqp.support.converter.SimpleMessageConverter;
import org.springframework.boot.autoconfigure.amqp.SimpleRabbitListenerContainerFactoryConfigurer;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

/**
 * Container exclusivo da DLQ. Mensagens mortas podem ter qualquer conteúdo
 * (inclusive JSON malformado), então aqui não há conversão para JSON nem retry:
 * se o listener da DLQ também tentasse converter, a mensagem falharia de novo
 * e seria descartada, porque a DLQ não tem outra dead letter exchange.
 */
@Configuration
public class DeadLetterListenerConfig {

    public static final String DLQ_CONTAINER_FACTORY = "dlqListenerContainerFactory";

    @Bean(DLQ_CONTAINER_FACTORY)
    public SimpleRabbitListenerContainerFactory dlqListenerContainerFactory(
            SimpleRabbitListenerContainerFactoryConfigurer configurer,
            ConnectionFactory connectionFactory) {

        SimpleRabbitListenerContainerFactory factory = new SimpleRabbitListenerContainerFactory();
        configurer.configure(factory, connectionFactory);
        factory.setMessageConverter(new SimpleMessageConverter());
        factory.setAdviceChain(); // sem retry
        return factory;
    }
}
