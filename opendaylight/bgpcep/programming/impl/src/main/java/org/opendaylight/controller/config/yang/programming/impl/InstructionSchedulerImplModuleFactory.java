/*
 * Copyright (c) 2013 Cisco Systems, Inc. and others.  All rights reserved.
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License v1.0 which accompanies this distribution,
 * and is available at http://www.eclipse.org/legal/epl-v10.html
 */
/**
 * Generated file

 * Generated from: yang module name: config-programming-impl  yang module local name: instruction-scheduler-impl
 * Generated by: org.opendaylight.controller.config.yangjmxgenerator.plugin.JMXGenerator
 * Generated at: Mon Nov 18 16:50:17 CET 2013
 *
 * Do not modify this file unless it is present under src/main directory
 */
package org.opendaylight.controller.config.yang.programming.impl;

import org.opendaylight.controller.config.api.DependencyResolver;
import org.opendaylight.controller.config.api.DynamicMBeanWithInstance;
import org.opendaylight.controller.config.spi.Module;
import org.osgi.framework.BundleContext;

/**
 * @deprecated Replaced by blueprint wiring
 */
public class InstructionSchedulerImplModuleFactory extends
        org.opendaylight.controller.config.yang.programming.impl.AbstractInstructionSchedulerImplModuleFactory {

    @Override
    public Module createModule(final String instanceName, final DependencyResolver dependencyResolver,
        final BundleContext bundleContext) {
        final InstructionSchedulerImplModule module = (InstructionSchedulerImplModule)
            super.createModule(instanceName, dependencyResolver, bundleContext);
        module.setBundleContext(bundleContext);
        return module;
    }

    @Override
    public Module createModule(final String instanceName, final DependencyResolver dependencyResolver,
        final DynamicMBeanWithInstance old, final BundleContext bundleContext) throws Exception {
        final InstructionSchedulerImplModule module = (InstructionSchedulerImplModule)
            super.createModule(instanceName, dependencyResolver, old, bundleContext);
        module.setBundleContext(bundleContext);
        return module;
    }
}
